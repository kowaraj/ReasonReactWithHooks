[@bs.module "./test"] [@bs.val] external http_req : (string, (string => unit)) => string = "";

let js_callback = msg => {
    Js.log("RETURN from the callback")
    Js.log(msg)
};

let req = (url) => {
  http_req(url, js_callback) |> ignore
};

type req_address = {
  hostname: string,
  page: string,
};

type state = {
  url: req_address
};

type action =
  | SetHostname(string)
  | SetPage(string)
;

let reducer_fun = (state, action) => {
  switch action {
    | SetHostname(hn) => { url: {hostname: hn, page: state.url.page}}
    | SetPage(p) => { url: {hostname: state.url.hostname, page: p}}
  }
};

[@react.component]
let make = () => {
  let (st, dispatch) = React.useReducer(
    reducer_fun,
    { url:
      { hostname: "http://ec2-34-246-176-2.eu-west-1.compute.amazonaws.com:3000",
        page: "/test"  }});

  let (req_url, setReqUrl) = React.useState( ()=> st.url.hostname ++ st.url.page);

  let handleClick = (_event) => {
    let r = st.url.hostname ++ st.url.page;
    Js.log("REQUESTING: "++r);
    req(r)
  };

  let valueFromEvent = (evt): string => evt->ReactEvent.Form.target##value;

  <div className="app">
      <p> {ReasonReact.string("Requested hostname: "++ st.url.hostname)} </p>
      <input
          value=st.url.hostname
          size=90
          type_="text"
          placeholder="Write something to do"
          onChange=( (evt) =>  { dispatch(SetHostname(valueFromEvent(evt))) })
          onKeyDown=( (evt) =>  { () })
      />
      <p> {ReasonReact.string("Requested page: "++ st.url.page)} </p>
      <input
          value=st.url.page
          type_="text"
          placeholder="Write something to do"
          onChange=( (evt) =>  { dispatch(SetPage(valueFromEvent(evt))) })
          onKeyDown=( (evt) =>  { () })
      />

      <p> {React.string( "Requested URL is: " ++ req_url)} </p>
      <button onClick={handleClick} > (ReasonReact.string("HTTP Request"))  </button>
  </div>
};











