open System

let sayHello person =
    printfn "Hello %s from my f# program " person

let isValid person =
    //not (String.IsNullOrWhiteSpace person)
    String.IsNullOrWhiteSpace person |> not

let isAllowed person =
    person <> "Eve"

[<EntryPoint>]
let main argv =
    argv
        |> Array.filter isValid
        |> Array.filter isAllowed
        |> Array.iter sayHello
        
    printfn "Nice to meet you"
    0

//[<EntryPoint>]
//let main argv =
//    Array.iter sayHello argv
//    printfn "Nice to meet you"
//    0

//[<EntryPoint>]
// let main argv =
// let person =
//    if argv.Length > 0 then
//        argv.[0]
//    else
//        "Anonymous Person"
// printfn "Hello %s from my F# program!" person

// for i in 0..argv.Length-1 do
//     let person = argv.[i]
//     printfn "Hello %s, nice to meet you " person

// for person in argv do
//     printfn "Hello %s, nice to meet you " person

// printfn "Nice to meet you"
// 0
