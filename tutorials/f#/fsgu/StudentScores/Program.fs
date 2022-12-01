open System
open System.IO

module Float =
    let tryFromString s =
        if s = "N/A" then
            None
        else
            Some (float s)

    //let fromStringOr50 s =
    //    if s = "N/A" then
    //        50.0;
    //    else
    //        float s

    //let fromStringOr50 s =
    //    s
    //    |> tryFromString
    //    |> Option.defaultValue 50.0
    let fromStringOr d s =
        s
        |> tryFromString
        |> Option.defaultValue d

type Student =
    {
        Name: string
        Id: string
        MeanScore:float
        MinScore:float
        MaxScore:float
    }

module Student =
    let fromString(s:string)=
        let elements = s.Split('\t')
        let name = elements.[0]
        let id = elements.[1]
        let scores =
            elements
            |> Array.skip 2
            //|> Array.map float
            //|> Array.choose Float.tryFromString
            //|> Array.map Float.fromStringOr50
            |> Array.map (Float.fromStringOr 50.0)
        let meanScore = scores|>Array.average
        let minScore = scores|>Array.min
        let maxScore = scores|>Array.max
        {
            Name=name
            Id=id
            MeanScore=meanScore
            MinScore=minScore
            MaxScore=maxScore
        }

    let printSummary(student:Student)=
        printfn "%s\t\t%s\t%0.1f\t%0.1f\t%0.1f" student.Name student.Id student.MinScore student.MaxScore student.MeanScore


let printMeanScore (row : string) = 
    let elements = row.Split('\t')
    let name = elements.[0]
    let id = elements.[1]
    //let meanScore =
    //    elements
    //    |> Array.skip 2
    //    //|> Array.map float
    //    //|> Array.average
    //    |> Array.averageBy float
    //printfn "%s\t%s\t%0.1f" name id meanScore
    let scores =
        elements
        |> Array.skip 2
        |> Array.map float
    let meanScore = scores|>Array.average
    let minScore = scores|>Array.min
    let maxScore = scores|>Array.max
    printfn "%s\t\t%s\t%0.1f\t%0.1f\t%0.1f" name id minScore maxScore meanScore


let summarize filePath = 
    let rows = File.ReadAllLines filePath
    let mutable studentCount = (rows |> Array.length)-1

    printfn "Student count %i" studentCount

    rows
    |> Array.skip 1
    |> Array.iter printMeanScore


let getSortKey(student: Student)=
    student.MeanScore

let summarizeWithRecord filePath = 
    let rows = File.ReadAllLines filePath
    let mutable studentCount = (rows |> Array.length)-1
    printfn "Student count %i" studentCount
    rows
    |> Array.skip 1
    |> Array.map Student.fromString
    //|> Array.sortByDescending getSortKey
    |>Array.sortByDescending (fun student -> student.MeanScore)
    |> Array.iter Student.printSummary

let summarizeWithRecordByName filePath = 
    let rows = File.ReadAllLines filePath
    let mutable studentCount = (rows |> Array.length)-1
    printfn "Student count %i" studentCount
    rows
    |> Array.skip 1
    |> Array.map Student.fromString
    |> Array.sortBy (fun student -> student.Name)
    |> Array.iter Student.printSummary

[<EntryPoint>]
let main argv =
    //summarizeWithRecord "Samples/StudentScores.txt"
    
    if argv.Length = 1 then
        let filePath = argv.[0]

        if File.Exists filePath then
            printfn "Processing %s" filePath
            summarizeWithRecord filePath
            printfn "\n=================\n"
            summarizeWithRecordByName filePath
            0
        else
            printfn "The file %s does not exists." filePath
            1

     else
        printfn "Please spicify a file"
        1

