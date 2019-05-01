[@bs.module "./test"] [@bs.val] external http_req : (string, (string => unit)) => string = "";

let js_callback = msg => {
    Js.log("RETURN from the callback")
    Js.log(msg)
};

let req = (url) => {
  http_req(url, js_callback) |> ignore
};

type req_address = {
  protocol: string,
  hostname: string,
  port: int,
  page: string,
};

type state = {
  url: req_address
};

type action =
  | SetProtocol(string)
  | SetHostname(string)
  | SetPort(int)
  | SetPage(string)
  | DoRequest
;

let handleDoRequest = (st) => {
    let r = st.url.protocol ++ "://" ++ st.url.hostname ++ ":" ++ string_of_int(st.url.port) ++ st.url.page;
    Js.log("DO-REQUESTING: "++r);
    req(r)
};
  
let reducer_fun = (state, action) => {
  switch action {
    | SetProtocol(proto) => { url: {...state.url, protocol: proto}}
    | SetHostname(hn) =>    { url: {...state.url, hostname: hn}}
    | SetPort(port) =>      { url: {...state.url, port: port}}
    | SetPage(p) =>         { url: {...state.url, page: p}}
    | DoRequest => {handleDoRequest(state); state}
  }
};


//http://ec2-34-246-176-2.eu-west-1.compute.amazonaws.com:3000/test1",
[@react.component]
let make = () => {
  let (st, dispatch) = React.useReducer(
    reducer_fun,
    { url:
      { protocol: "http", 
        hostname: "localhost", //ec2-34-246-176-2.eu-west-1.compute.amazonaws.com",
        port: 3000, 
        page: "/test1"  }});

  let (req_url, setReqUrl) = React.useState( ()=> st.url.hostname ++ st.url.page);

  let handleClick = (_event) => {
    let r = st.url.protocol ++ "://" ++ st.url.hostname ++ ":" ++ string_of_int(st.url.port) ++ st.url.page;
    Js.log("REQUESTING: "++r);
    req(r)
  };

  let valueFromEvent = (evt): string => evt->ReactEvent.Form.target##value;

  <div className="app">

      // PROTOCOL INPUT
      <p> {ReasonReact.string("Requested protocol: "++ st.url.protocol)} </p>
      <input
          value=st.url.protocol
          size=90
          type_="text"
          placeholder="Write something to do"
          onChange=( (evt) =>  { dispatch(SetProtocol(valueFromEvent(evt))) })
          onKeyDown=( (evt) =>  { 
            if (ReactEvent.Keyboard.key(evt) == "Enter") {
              dispatch(DoRequest) }})

      />

      // HOSTNAME INPUT
      <p> {ReasonReact.string("Requested hostname: "++ st.url.hostname)} </p>
      <input
          value=st.url.hostname
          size=90
          type_="text"
          placeholder="Write something to do"
          onChange=( (evt) =>  { dispatch(SetHostname(valueFromEvent(evt))) })
          onKeyDown=( (evt) =>  { () })
      />

      // PORT INPUT
      <p> {ReasonReact.string("Requested port: "++ string_of_int(st.url.port))} </p>
      <input
          value=string_of_int(st.url.port)
          type_="text"
          placeholder="Write something to do"
          onChange=( (evt) =>  { dispatch(SetPort(int_of_string(valueFromEvent(evt)))) })
          onKeyDown=( (evt) =>  { () })
      />

      // PAGE INPUT
      <p> {ReasonReact.string("Requested page: "++ st.url.page)} </p>
      <input
          value=st.url.page
          type_="text"
          placeholder="Write something to do"
          onChange=( (evt) =>  { dispatch(SetPage(valueFromEvent(evt))) })
          onKeyDown=( (evt) =>  { () })
      />

      // RESULTING URL
      <p> {React.string( "Requested URL is: " ++ req_url)} </p>
      <button onClick={handleClick} > (ReasonReact.string("HTTP Request"))  </button>
  </div>
};











