open System
open System.IO
open StudentScores

[<EntryPoint>]
let main argv =
    // Summary.summarize "Samples/StudentScores.txt"
    if argv.Length = 1 then
        let filePath = argv.[0]

        if File.Exists filePath then
            printfn "Processing %s" filePath
            try
                Summary.summarize filePath
                0
            with
            | :? FormatException as e ->
                printfn "Error: %s " e.Message
                printfn "The file was not in the expected format."
                1
            | :? IO.IOException as e ->
                printfn "Error: %s " e.Message
                printfn "The input file is being used."
                1
            | _ as e ->
                printfn "Unexpected error: %s " e.Message
                1
        else
            printfn "The file %s does not exists." filePath
            1

     else
        printfn "Please spicify a file"
        1

//[<EntryPoint>]
//let main argv =
//    //summarizeWithRecord "Samples/StudentScores.txt"
    
//    if argv.Length = 1 then
//        let filePath = argv.[0]

//        if File.Exists filePath then
//            printfn "Processing %s" filePath
//            Summary.summarizeWithRecord filePath
//            printfn "\n=================\n"
//            //summarizeWithRecordByName filePath
//            0
//        else
//            printfn "The file %s does not exists." filePath
//            1

//     else
//        printfn "Please spicify a file"
//        1

