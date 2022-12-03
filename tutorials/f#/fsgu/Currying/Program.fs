open System

let add a b =
    a+b

let c = add 2 3

let d = add 2

let e = d 4

let quote symbol s=
    sprintf "%c%s%c" symbol s symbol

let singleQuote = quote '\''
let doubleQuote = quote '"'


[<EntryPoint>]
let main argv =
    printfn "c: %i" c
    printfn "e: %i" e

    printfn "%s" (singleQuote "It was the best of times.")
    printfn "%s" (doubleQuote "It was the best of times.")

    0

//curried parameters -> partial application.
