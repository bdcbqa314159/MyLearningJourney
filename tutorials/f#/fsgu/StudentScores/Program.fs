open System
open System.IO
open StudentScores

[<EntryPoint>]
let main argv =
    
    if argv.Length = 1 then
        let filePath = argv.[0]

        if File.Exists filePath then
            printfn "Processing %s" filePath
            Summary.summarize filePath
            0
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

