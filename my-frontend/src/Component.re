[@bs.module "./test"] [@bs.val] external http_req : (string, (string => unit)) => string = "";


type req_address = {
  protocol: string,
  hostname: string,
  port: int,
  page: string,
};

type state = {
  url: req_address,
};

type state_2 = {
  req_response: string
};

type action =
  | SetProtocol(string)
  | SetHostname(string)
  | SetPort(int)
  | SetPage(string)
  | DoRequest
;

type action_2 =
  | SetResponse(string)
;


//http://ec2-34-246-176-2.eu-west-1.compute.amazonaws.com:3000/test1",
[@react.component]
let make = () => 
{

  let reducer_fun_2 = (_state, action) => {
    switch action {
    | SetResponse(resp) =>  {req_response: resp}
    }
  };

  let (st_2, dispatch_2) = React.useReducer(
    reducer_fun_2,
    {req_response: "nothing has been requested"}
  );

  let js_callback = msg => {
    Js.log("RETURN from the callback");
    Js.log(msg);
    dispatch_2(SetResponse(msg))
      
  };

  let req = (url) => {
    http_req(url, js_callback) |> ignore
  };

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
    | DoRequest =>          { handleDoRequest(state); state }
    }
  };

  let (st, dispatch) = React.useReducer(
    reducer_fun,
    { url:
      { protocol: "http", 
        hostname: "localhost", //ec2-34-246-176-2.eu-west-1.compute.amazonaws.com",
        port: 3000, 
        page: "/test"  }
  });

  

  /* let (req_url, setReqUrl) = React.useState( ()=> st.url.hostname ++ st.url.page); */

  let handleButtonClick = (_event) => {
    let r = st.url.protocol ++ "://" ++ st.url.hostname ++ ":" ++ string_of_int(st.url.port) ++ st.url.page;
    Js.log("BUTTON REQUESTING: "++r);
    req(r)
  };

  let valueFromEvent = (evt): string => evt->ReactEvent.Form.target##value;

  let dispatchOnEnter = (evt) =>  { 
    if (ReactEvent.Keyboard.key(evt) == "Enter") {
      dispatch(DoRequest);
    }};


  <div className="app">

      // PROTOCOL INPUT
      <p> {ReasonReact.string("Requested protocol: "++ st.url.protocol)} </p>
      <input
          value=st.url.protocol
          size=90
          type_="text"
          placeholder="Write something to do"
          onChange=( (evt) =>  { dispatch(SetProtocol(valueFromEvent(evt))) })
          onKeyDown=dispatchOnEnter
      />

      // HOSTNAME INPUT
      <p> {ReasonReact.string("Requested hostname: "++ st.url.hostname)} </p>
      <input
          value=st.url.hostname
          size=90
          type_="text"
          placeholder="Write something to do"
          onChange=( (evt) =>  { dispatch(SetHostname(valueFromEvent(evt))) })
          onKeyDown=dispatchOnEnter
      />

      // PORT INPUT
      <p> {ReasonReact.string("Requested port: "++ string_of_int(st.url.port))} </p>
      <input
          value=string_of_int(st.url.port)
          type_="text"
          placeholder="Write something to do"
          onChange=( (evt) =>  { dispatch(SetPort(int_of_string(valueFromEvent(evt)))) })
          onKeyDown=dispatchOnEnter
      />

      // PAGE INPUT
      <p> {ReasonReact.string("Requested page: "++ st.url.page)} </p>
      <input
          value=st.url.page
          type_="text"
          placeholder="Write something to do"
          onChange=( (evt) =>  { dispatch(SetPage(valueFromEvent(evt))) })
          onKeyDown=dispatchOnEnter
      />

      // RESULTING URL

      <p style=(ReactDOMRe.Style.make(~fontWeight="bold", ()))> { 
            let r = st.url.protocol ++ "://" ++ st.url.hostname ++ ":" ++ string_of_int(st.url.port) ++ st.url.page;
            React.string( "Request URL:   " ++ r) }</p>
      <button onClick={handleButtonClick} > (ReasonReact.string("HTTP Request"))  </button>
      <p> { React.string( "Response to the HTTP request is: ") } </p>
      <p style=(ReactDOMRe.Style.make(~backgroundColor="lightGrey", ()))> { 
        React.string( "\n " ++ st_2.req_response)} </p>
  </div>
};











