[@bs.val] external basePath: string = "basePath";
let basePathList = Js.Array.filter((s) => s !== "", Js.String.split("/", basePath));


[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  let path = url.path
    -> Belt.List.drop(Js.Array.length(basePathList))
    -> (urlPath => {
      switch (urlPath) {
      | Some(list) => list
      | None => []
      };
    });

  switch (path) {
    | ["login"] => <LoginPage />;
    | _ => <div>{ReasonReact.string("404")}</div>
  }
}