namespace StudentScores

open StudentScores

type Student =
    {
        Surname: string
        GivenName: string
        //Name: string
        Id: string
        MeanScore:float
        MinScore:float
        MaxScore:float
    }

//The importance of type annotations.
module Student =
    let namePart i (s:string)=
        let elements = s.Split(',')
        elements.[i].Trim()

    let fromString(s:string)=
        let elements = s.Split('\t')
        let name = elements.[0]
        let given = namePart 1 name
        let sur = namePart 0 name
        let id = elements.[1]
        let scores =
            elements
            |> Array.skip 2
            //|> Array.map float
            //|> Array.choose Float.tryFromString
            //|> Array.map Float.fromStringOr50
            |> Array.map (Float.fromStringOr 50.0)
            //If let fromStringOr(d,s)=(...)
            //|> Array.map (fun s -> Float.fromStringOr(50.0, s))
        let meanScore = scores|>Array.average
        let minScore = scores|>Array.min
        let maxScore = scores|>Array.max
        {
            //Name=name
            Surname = sur
            GivenName = given
            Id=id
            MeanScore=meanScore
            MinScore=minScore
            MaxScore=maxScore
        }

    let printSummary(student:Student)=
        //printfn "%s\t\t%s\t%0.1f\t%0.1f\t%0.1f" student.Name student.Id student.MinScore student.MaxScore student.MeanScore
        printfn "%s\t%s\t\t%s\t%0.1f\t%0.1f\t%0.1f" student.Surname student.GivenName student.Id student.MinScore student.MaxScore student.MeanScore

