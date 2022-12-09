namespace ColorManagement

open System.Drawing

type ColorHistory(initialColors: seq<Color>, maxlength: int)=
    let mutable colors = 
        initialColors 
        |>Seq.truncate maxlength
        |>List.ofSeq
    member this.Colors() = 
        colors|>Seq.ofList
    
    member this.Add(color: Color) = 
        let colors' = 
            color::colors
            |>List.distinct
            |>List.truncate maxlength
        colors<-colors'
    
    member this.TryLatest() = 
        match colors with
        |head::_->
            head|>Some
        |[]->
            None

    member this.RemoveLatest()=
        match colors with
        |_::tail->
            colors<- tail
        |[]->
            ()