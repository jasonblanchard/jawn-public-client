// TODO: Inject these a better way
[@bs.val] external homepagePath: string = "homepagePath";
[@bs.val] external authApiPath: string = "authApiPath";

type state = {
  didLoginSubmitFail: bool,
  isLoginSubmitting: bool
};

type action =
  | LoginFormSubmited
  | LoginFormSubmitSucceeded
  | LoginFormSubmitFailed;

type submitPayload = {
  username: string,
  password: string
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer((state, action) => {
    switch (action) {
      | LoginFormSubmited => {isLoginSubmitting: true, didLoginSubmitFail: false }
      | LoginFormSubmitSucceeded => {...state, isLoginSubmitting: false }
      | LoginFormSubmitFailed => {didLoginSubmitFail: true, isLoginSubmitting: false }
    }
  }, { didLoginSubmitFail: false, isLoginSubmitting: false });

  let handleSubmit = (username, password) => {
    Js.log({j|Called with username: $username password $password|j});
    let payload = Js.Dict.empty();
    Js.Dict.set(payload, "username", Js.Json.string(username));
    Js.Dict.set(payload, "password", Js.Json.string(password));
    ignore(Js.Promise.(
      Fetch.fetchWithInit(
        authApiPath,
        Fetch.RequestInit.make(
          ~method_=Post,
          ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
          ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
          ()
          )
        )
      |> then_(response => {
        switch (Fetch.Response.ok(response)) {
          | true => {
            Navigation.hardLink(homepagePath);
            resolve();
          }
          | false => {
            dispatch(LoginFormSubmitFailed);
            resolve();
          }
        }
      })
      |> catch(error => {
        Js.log(error);
        dispatch(LoginFormSubmitFailed);
        resolve();
      })
    ));
    ();
  };

  <Layout>
    <LoginForm 
      didSubmitFail={state.didLoginSubmitFail}
      isSubmitting={state.isLoginSubmitting}
      onSubmit={handleSubmit}
    />
  </Layout>
};