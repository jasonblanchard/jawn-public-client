// TODO: Move somewhere else// TODO: Move somewhere else
let validateUsername = (username) => {
  switch (username) {
      | None | Some("") => Some("Username Can't be empty")
      | Some(_) => None;
  };
};

// TODO: Move somewhere else// TODO: Move somewhere else
let validatePassword = (password) => {
  switch (password) {
      | None | Some("") => Some("Password Can't be empty")
      | Some(_) => None;
  };
};

type formValues = {
  .
  "username": string,
  "password": string
};

[@react.component]
let make = (~didSubmitFail, ~isSubmitting, ~onSubmit) => {
  let onSubmit = (values: formValues) => {
    let username = values##username;
    let password = values##password;
    onSubmit(username, password);
  };

  let { ReactFinalFormHooks.Hooks.pristine, handleSubmit, form, valid } = ReactFinalFormHooks.Hooks.useForm(~onSubmit=onSubmit, ());

  let username = ReactFinalFormHooks.Hooks.useField(~name="username", ~form=form, ~validate=validateUsername, ());
  let password = ReactFinalFormHooks.Hooks.useField(~name="password", ~form=form, ~validate=validatePassword, ());

  let usernameErrorMessage =
    switch (username.meta.touched, username.meta.valid) {
    | (true, false) => ReasonReact.string(username.meta.error)
    | (false, _) => ReasonReact.null
    | (true, true) => ReasonReact.null
  };

  let passwordErrorMessage =
    switch (password.meta.touched, password.meta.valid) {
    | (true, false) => ReasonReact.string(password.meta.error)
    | (false, _) => ReasonReact.null
    | (true, true) => ReasonReact.null
  };

  let submitError = switch(didSubmitFail) {
    | true => ReasonReact.string("nope")
    | false => ReasonReact.null
  };

  let disabled = switch(pristine, valid, isSubmitting) {
    | (_, _, true) => true
    | (true, _, _) => true
    | (_, false, _) => true
    | (false, true, _) => false
  };

  <form onSubmit={handleSubmit}>
    <div>
      <label htmlFor={username.input.name}>
        {usernameErrorMessage}
        <br />
        {ReasonReact.string("Username")}
      </label>
      <input
        name={username.input.name}
        value={username.input.value}
        onChange={username.input.onChange}
        onBlur={username.input.onBlur}
        onFocus={username.input.onFocus}
        id={username.input.name}
      />
    </div>
    <div>
      <label htmlFor={password.input.name}>
        {passwordErrorMessage}
        <br />
        {ReasonReact.string("password")}
      </label>
      <input
        name={password.input.name}
        value={password.input.value}
        onChange={password.input.onChange}
        onBlur={password.input.onBlur}
        onFocus={password.input.onFocus}
        id={password.input.name}
        type_="password"
      />
    </div>
    <button disabled={disabled}>{ReasonReact.string("login")}</button>
    <div>
      submitError
    </div>
  </form>
};