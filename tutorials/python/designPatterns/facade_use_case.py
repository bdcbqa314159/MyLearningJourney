import time
from decimal import Decimal


class Reports():
    "a singleton dictionary of reported events"
    _reports: dict[int, tuple[float, str]] = {}
    _row_id = 0

    def __new__(cls):
        return cls

    @classmethod
    def get_history(cls) -> dict:
        "a method to retrieve all historic events"
        return cls._reports

    @classmethod
    def log_event(cls, event: str) -> bool:
        "a method to add a new event to the record"
        cls._reports[cls._row_id] = (time.time(), event)
        cls._row_id += 1
        return True


class Wallets():
    "a singleton dictionary of user wallets"
    _wallets: dict[str, Decimal] = {}

    def __new__(cls):
        return cls

    @classmethod
    def create_wallet(cls, user_id: str) -> bool:
        "a method to initialize a users wallet"
        if not user_id in cls._wallets:
            cls._wallets[user_id] = Decimal('0')
            Reports.log_event(
                f"wallet for `{user_id}` created and set to 0")
            return True
        return False

    @classmethod
    def get_balance(cls, user_id: str) -> Decimal:
        "a method to check a users balance"
        Reports.log_event(
            f"balance check for `{user_id}` = {cls._wallets[user_id]}")
        return cls._wallets[user_id]

    @classmethod
    def adjust_balance(cls, user_id: str, amount: Decimal) -> Decimal:
        "a method to adjust a user balance up or down"
        cls._wallets[user_id] += Decimal(amount)
        Reports.log_event(f"Balance adjustment for `{user_id}`. "
                          f"New balance = {cls._wallets[user_id]}"
                          )
        return cls._wallets[user_id]


class Users():
    "a singleton dictionary of users"

    _users: dict[str, dict[str, str]] = {}

    def __new__(cls):
        return cls

    @classmethod
    def register_user(cls, new_user: dict[str, str]) -> str:
        "register a user"
        if not new_user["user_name"] in cls._users:
            user_id = new_user["user_name"]
            cls._users[user_id] = new_user
            Reports.log_event(f"new user `{user_id}` created")
            Wallets().create_wallet(user_id)

            Reports.log_event(
                f"Give new user `{user_id}` sign up bonus of 10"
            )
            Wallets().adjust_balance(user_id, Decimal(10))
            return user_id

        return ""

    @classmethod
    def edit_user(cls, user_id: str, user: dict):
        "do nothing"
        print(user_id)
        print(user)

        return False

    @classmethod
    def change_pwd(cls, user_id: str, password: str):
        "do nothing"
        print(user_id)
        print(password)
        return False


class GameEngine():
    "the Game Engine"
    _instance = None
    _start_time: int = 0
    _clock: int = 0
    _entries: list[tuple[str, Decimal]] = []
    _game_open = True

    def __new__(cls):
        if cls._instance is None:
            cls._instance = GameEngine
            cls._start_time = int(time.time())
            cls._clock = 60

        return cls._instance

    @classmethod
    def get_game_state(cls) -> dict:
        "get a snapshot of the current game state"
        now = int(time.time())
        time_remaining = cls._start_time - now + cls._clock
        if time_remaining < 0:
            time_remaining = 0
            cls._game_open = False
        return {
            "clock": time_remaining,
            "game_open": cls._game_open,
            "entries": cls._entries
        }

    @classmethod
    def submit_entry(cls, user_id: str, entry: Decimal) -> bool:
        "submit a new entry for the user in this game"
        now = int(time.time())
        time_remaining = cls._start_time - now + cls._clock
        if time_remaining > 0:
            if Wallets.get_balance(user_id) > Decimal('1'):
                if Wallets.adjust_balance(user_id, Decimal('-1')):
                    cls._entries.append((user_id, entry))
                    Reports.log_event(
                        f"New entry `{entry}` submitted by `{user_id}`"
                    )
                    return True
                Reports.log_event(
                    f"Problem adjusting balance for `{user_id}`"
                )
                return False
            Reports.log_event(f"User Balance for `{user_id}` to low")
            return False

        Reports.log_event("Game Closed")

        return False


class GameAPI():
    "the game api facade"
    @staticmethod
    def get_balance(user_id: str) -> Decimal:
        "get a players balance"
        return Wallets.get_balance(user_id)

    @staticmethod
    def game_state() -> dict:
        "get the current game state"
        return GameEngine().get_game_state()

    @staticmethod
    def get_history() -> dict:
        "get the game history"
        return Reports.get_history()

    @staticmethod
    def change_pwd(user_id: str, password: str) -> bool:
        "change users password"
        return Users.change_pwd(user_id, password)

    @staticmethod
    def submit_entry(user_id: str, entry: Decimal) -> bool:
        "submit a bet"
        return GameEngine().submit_entry(user_id, entry)

    @staticmethod
    def register_user(value: dict[str, str]) -> str:
        "register a new user and returns the new id"
        return Users.register_user(value)


if __name__ == "__main__":
    user = {"user_name": "bernardo"}
    user_id = GameAPI.register_user(user)

    time.sleep(1)

    GameAPI.submit_entry(user_id, Decimal('5'))

    time.sleep(1)

    print()
    print("---- Gamestate Snapshot ----")
    print(GameAPI.game_state())
    time.sleep(1)

    history = GameAPI.get_history()
    print()
    print("---- Reports History ----")

    for row in history:
        print(f"{row} : {history[row][0]} : {history[row][1]}")

    print()
    print("---- Gamestate Snapshot ----")
    print(GameAPI.game_state())
