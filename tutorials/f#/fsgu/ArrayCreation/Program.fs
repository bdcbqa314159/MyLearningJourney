open System

module Drunkard = 
    let r = System.Random()

    let step()=
        r.Next(-1, 2)
    
    type Position = {X: int; Y:int}

    let walk = 
        {X = 0; Y = 0}
        |> Seq.unfold(fun position ->
            let x' = position.X + step()
            let y' = position.Y + step()
            let position' = {X = x'; Y = y'}
            Some(position', position'))


module MathSequence = 

    type State = {N: int; Pn2: int; Pn1: int}

    let pell = 
        // (0,0,0)
        {N = 0; Pn2 = 0; Pn1 = 0}
        // |>Seq.unfold(fun(n, pn2, pn1)->
        |>Seq.unfold (fun state ->
            let pn = 
                match state.N with
                | 0 | 1
                    -> state.N
                | _
                    -> 2*state.Pn1 + state.Pn2
            let n' = state.N+1
            Some(pn, {N = n'; Pn2 = state.Pn1; Pn1 = pn}))


[<EntryPoint>]
let main argv=

    let isEven x =
        x%2 = 0

    let numbers = 
        [|
            for i in 1..9 do
                let x = i *i
                if x|> isEven then
                    x
        |]
    
    printfn "%A" numbers

    let total =
        [|
            for i in 1..1000 do
                yield i*i
        |]
        |> Array.sum
    printfn "The sum of the array is %i" total

    let total1 = 
        Array.init 1000 (fun i -> 
            let x = i+1
            x*x)
        |>Array.sum

    printfn "Another way to have the result above: %i " total1
    printfn "T es un mec genial!"

    let initialZeroes = Array.zeroCreate<int> 10

    printf "%A\n" initialZeroes

    initialZeroes.[0] <- 42


    printf "%A\n" initialZeroes

    printfn "Working with sequences!\n"

    let total_seq = 
        seq { for i in 1..1000 -> i*i}
        |> Seq.sum

    printfn "The result is %i " total_seq

    let total_seq1 = 
        Seq.init 1000 (fun i -> 
            let x = i+1
            x*x)
        |>Seq.sum
    
    printfn "Resultat %i " total_seq1

    let squares = 
        Seq.initInfinite (fun i ->
            let x = i+1
            x*x)
    let total_seq2 = 
        squares
        |> Seq.truncate 1000
        |> Seq.sum

    printfn "Resultat %i " total_seq2

    MathSequence.pell
    |> Seq.truncate 10
    |> Seq.iter (fun x -> printf "%i, " x)

    printfn "..."

    printf "Drunkard's walk"
    Drunkard.walk
    |> Seq.take 100
    |> Seq.iter (fun p -> printfn "X %i Y: %i" p.X p.Y)

    0

