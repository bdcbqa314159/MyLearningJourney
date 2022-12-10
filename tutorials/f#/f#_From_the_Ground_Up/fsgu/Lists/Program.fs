open System
open System.Drawing
open ColorManagement

let listColors(history: ColorHistory)=
    history.Colors()
    |>Seq.iter(printf "%A")
    printfn ""

[<EntryPoint>]
let main argv =
    printfn "Hello f#!"

    let strings = ["the"; "cat"; "sat"]
    printfn "strings: %A" strings

    let strings1 = "sometimes"::strings
    printfn "strings1: %A" strings1


    match strings1 with
    | head::tail->
        printfn "head: \"%s\", tail: %A" head tail
    | []->
        printfn "Empty list"


    printf "I can create a color history with some colors: "
    let history = ColorHistory([Color.Indigo; Color.Violet], 7)
    history|> listColors

    printfn "I can add color:"
    history.Add(Color.Blue)
    history|> listColors
    printfn "The new color is the latest: "
    printfn "%O" (history.TryLatest())



    0