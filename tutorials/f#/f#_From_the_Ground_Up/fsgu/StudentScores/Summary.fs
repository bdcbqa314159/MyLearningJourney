namespace StudentScores

module Summary =
    open System.IO

    let printGroupSummary (surname: string) (students: Student[]) =
        printfn "%s" (surname.ToUpperInvariant())

        students
        |> Array.sortBy (fun student -> 
            student.GivenName, student.Id)
        |> Array.iter (fun student ->
            printfn
                "\t%20s\t%s\t%0.1f\t%0.1f\t%0.1f"
                student.GivenName
                student.Id
                student.MeanScore
                student.MinScore
                student.MaxScore)

    let summarize filePath = 
        let rows = File.ReadAllLines filePath
        let mutable studentCount = (rows |> Array.length)-1
        printfn "Student count %i" studentCount
        rows
        |> Array.skip 1
        |> Array.map Student.fromString
        // |>Array.sortByDescending (fun student -> student.MeanScore)
        // |> Array.iter Student.printSummary
        |> Array.groupBy (fun s -> s.Surname)
        |> Array.sortBy fst
        |> Array.iter (fun (surname, students)->
        printGroupSummary surname students)



////Tuple in f# x*y -> (x,y)

//let printMeanScore (row : string) = 
//    let elements = row.Split('\t')
//    let name = elements.[0]
//    let id = elements.[1]
//    //let meanScore =
//    //    elements
//    //    |> Array.skip 2
//    //    //|> Array.map float
//    //    //|> Array.average
//    //    |> Array.averageBy float
//    //printfn "%s\t%s\t%0.1f" name id meanScore
//    let scores =
//        elements
//        |> Array.skip 2
//        |> Array.map float
//    let meanScore = scores|>Array.average
//    let minScore = scores|>Array.min
//    let maxScore = scores|>Array.max
//    printfn "%s\t\t%s\t%0.1f\t%0.1f\t%0.1f" name id minScore maxScore meanScore


//let summarize filePath = 
//    let rows = File.ReadAllLines filePath
//    let mutable studentCount = (rows |> Array.length)-1

//    printfn "Student count %i" studentCount

//    rows
//    |> Array.skip 1
//    |> Array.iter printMeanScore


//let getSortKey(student: Student)=
//    student.MeanScore

////let summarizeWithRecordByName filePath = 
////    let rows = File.ReadAllLines filePath
////    let mutable studentCount = (rows |> Array.length)-1
////    printfn "Student count %i" studentCount
////    rows
////    |> Array.skip 1
////    |> Array.map Student.fromString
////    |> Array.sortBy (fun student -> student.Name)
////    |> Array.iter Student.printSummary