namespace StudentScores

type Student =
    {
        Surname: string
        GivenName: string
        Id: string
        MeanScore:float
        MinScore:float
        MaxScore:float
    }

module Student =

    let nameParts (s : string) =
        let elements = s.Split(',')
        match elements with
        | [|surname; givenName|] -> 
            {| Surname = surname.Trim()
               GivenName = givenName.Trim() |}
        | [|surname|] ->
            {| Surname = surname.Trim()
               GivenName = "(None)" |}
        | _ -> 
            raise (System.FormatException(sprintf "Invalid student name format: \"%s\"" s))
 
    let fromString (s : string) =
        let elements = s.Split('\t')
        let name = elements.[0] |> nameParts
        let id = elements.[1]    
        let scores =
            elements
            |> Array.skip 2
            |> Array.map TestResult.fromString
            |> Array.choose TestResult.tryEffectiveScore
        let meanScore = scores |> Array.average
        let minScore = scores |> Array.min
        let maxScore = scores |> Array.max
        {
            Surname = name.Surname
            GivenName = name.GivenName
            Id = id
            MeanScore = meanScore
            MinScore = minScore
            MaxScore = maxScore
        }
 
    let printSummary (student : Student) =
        printfn "%s, %s\t%s\t%0.1f\t%0.1f\t%0.1f" student.Surname student.GivenName student.Id student.MeanScore student.MinScore student.MaxScore



    //let namePart i (s:string)=
    //    let elements = s.Split(',')
    //    elements.[i].Trim()
        
    //let nameParts (s:string)=
    //    let elements = s.Split(',')
    //    let surname = elements.[0].Trim()
    //    let givenName = elements.[1].Trim()
    //    (surname, givenName)

    //let nameParts (s:string)=
    //    let elements = s.Split(',')
    //    match elements with
    //    //|[|surname; givenName|] ->
    //    //    surname.Trim(), givenName.Trim()
    //    //|[|surname|] ->
    //    //    surname.Trim(), "(None)"
    //    | [|surname; givenName|] ->
    //        {|Surname = surname.Trim()
    //            GivenName = givenName.Trim() |}
    //    |[|surname|] ->
    //        {|Surname = surname.Trim()
    //        GivenName = "(None)" |}
    //    | _ ->
    //        raise (System.FormatException("Invalid name format."))

    //let fromString(s:string)=
    //    let elements = s.Split('\t')
    //    //let name = elements.[0]
    //    //let given = namePart 1 name
    //    //let sur = namePart 0 name
    //    //let sur, given = name |> nameParts
    //    let name = elements.[0] |> nameParts
    //    let id = elements.[1]
    //    let scores =
    //        elements
    //        |> Array.skip 2
    //        //|> Array.map (Float.fromStringOr 50.0)
    //        |> Array.map TestResult.fromString
    //        //|> Array.map TestResult.effectiveScore
    //        |> Array.choose TestResult.tryEffectiveScore
  
    //    let meanScore = scores|>Array.average
    //    let minScore = scores|>Array.min
    //    let maxScore = scores|>Array.max
    //    {
            
    //        //Surname = sur
    //        //GivenName = given
    //        Surname = name.Surname
    //        GivenName = name.GivenName
    //        Id=id
    //        MeanScore=meanScore
    //        MinScore=minScore
    //        MaxScore=maxScore
    //    }

    //let printSummary(student:Student) =
    //    printfn "%s\t%s\t\t%s\t%0.1f\t%0.1f\t%0.1f" student.Surname student.GivenName student.Id student.MinScore student.MaxScore student.MeanScore


//type Student =
//    {
//        Surname: string
//        GivenName: string
//        //Name: string
//        Id: string
//        MeanScore:float
//        MinScore:float
//        MaxScore:float
//    }

////The importance of type annotations.
//module Student =
//    let namePart i (s:string)=
//        let elements = s.Split(',')
//        elements.[i].Trim()

//    let fromString(s:string)=
//        let elements = s.Split('\t')
//        let name = elements.[0]
//        let given = namePart 1 name
//        let sur = namePart 0 name
//        let id = elements.[1]
//        let scores =
//            elements
//            |> Array.skip 2
//            //|> Array.map float
//            //|> Array.choose Float.tryFromString
//            //|> Array.map Float.fromStringOr50
//            |> Array.map (Float.fromStringOr 50.0)
//            //If let fromStringOr(d,s)=(...)
//            //|> Array.map (fun s -> Float.fromStringOr(50.0, s))
//        let meanScore = scores|>Array.average
//        let minScore = scores|>Array.min
//        let maxScore = scores|>Array.max
//        {
//            //Name=name
//            Surname = sur
//            GivenName = given
//            Id=id
//            MeanScore=meanScore
//            MinScore=minScore
//            MaxScore=maxScore
//        }

//    let printSummary(student:Student)=
//        //printfn "%s\t\t%s\t%0.1f\t%0.1f\t%0.1f" student.Name student.Id student.MinScore student.MaxScore student.MeanScore
//        printfn "%s\t%s\t\t%s\t%0.1f\t%0.1f\t%0.1f" student.Surname student.GivenName student.Id student.MinScore student.MaxScore student.MeanScore

