[@react.component]
let make = (~children) => 
  <div className="Layout">
    {ReasonReact.string("Jawn")}
    children
  </div>