// Generated by BUCKLESCRIPT VERSION 5.0.3, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Test = require("./test");
var Caml_format = require("bs-platform/lib/js/caml_format.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");

function http_req(prim, prim$1) {
  return Test.http_req(prim, prim$1);
}

function Component(Props) {
  var reducer_fun_2 = function (state, action) {
    if (typeof action === "number") {
      throw [
            Caml_builtin_exceptions.match_failure,
            /* tuple */[
              "Component.re",
              34,
              41
            ]
          ];
    } else if (action.tag === 4) {
      return /* record */[/* req_response */action[0]];
    } else {
      throw [
            Caml_builtin_exceptions.match_failure,
            /* tuple */[
              "Component.re",
              34,
              41
            ]
          ];
    }
  };
  var match = React.useReducer(reducer_fun_2, /* record */[/* req_response */"nothing has been requested"]);
  var dispatch_2 = match[1];
  var js_callback = function (msg) {
    console.log("RETURN from the callback");
    console.log(msg);
    return Curry._1(dispatch_2, /* SetResponse */Block.__(4, [msg]));
  };
  var req = function (url) {
    Test.http_req(url, js_callback);
    return /* () */0;
  };
  var handleDoRequest = function (st) {
    var r = st[/* url */0][/* protocol */0] + ("://" + (st[/* url */0][/* hostname */1] + (":" + (String(st[/* url */0][/* port */2]) + st[/* url */0][/* page */3]))));
    console.log("DO-REQUESTING: " + r);
    return req(r);
  };
  var reducer_fun = function (state, action) {
    if (typeof action === "number") {
      handleDoRequest(state);
      return state;
    } else {
      switch (action.tag | 0) {
        case 0 : 
            var init = state[/* url */0];
            return /* record */[/* url : record */[
                      /* protocol */action[0],
                      /* hostname */init[/* hostname */1],
                      /* port */init[/* port */2],
                      /* page */init[/* page */3]
                    ]];
        case 1 : 
            var init$1 = state[/* url */0];
            return /* record */[/* url : record */[
                      /* protocol */init$1[/* protocol */0],
                      /* hostname */action[0],
                      /* port */init$1[/* port */2],
                      /* page */init$1[/* page */3]
                    ]];
        case 2 : 
            var init$2 = state[/* url */0];
            return /* record */[/* url : record */[
                      /* protocol */init$2[/* protocol */0],
                      /* hostname */init$2[/* hostname */1],
                      /* port */action[0],
                      /* page */init$2[/* page */3]
                    ]];
        case 3 : 
            var init$3 = state[/* url */0];
            return /* record */[/* url : record */[
                      /* protocol */init$3[/* protocol */0],
                      /* hostname */init$3[/* hostname */1],
                      /* port */init$3[/* port */2],
                      /* page */action[0]
                    ]];
        case 4 : 
            throw [
                  Caml_builtin_exceptions.match_failure,
                  /* tuple */[
                    "Component.re",
                    62,
                    39
                  ]
                ];
        
      }
    }
  };
  var match$1 = React.useReducer(reducer_fun, /* record */[/* url : record */[
          /* protocol */"http",
          /* hostname */"localhost",
          /* port */3000,
          /* page */"/test"
        ]]);
  var dispatch = match$1[1];
  var st = match$1[0];
  var handleButtonClick = function (_event) {
    var r = st[/* url */0][/* protocol */0] + ("://" + (st[/* url */0][/* hostname */1] + (":" + (String(st[/* url */0][/* port */2]) + st[/* url */0][/* page */3]))));
    console.log("BUTTON REQUESTING: " + r);
    return req(r);
  };
  var dispatchOnEnter = function (evt) {
    if (evt.key === "Enter") {
      return Curry._1(dispatch, /* DoRequest */0);
    } else {
      return 0;
    }
  };
  var r = st[/* url */0][/* protocol */0] + ("://" + (st[/* url */0][/* hostname */1] + (":" + (String(st[/* url */0][/* port */2]) + st[/* url */0][/* page */3]))));
  return React.createElement("div", {
              className: "app"
            }, React.createElement("p", undefined, "Requested protocol: " + st[/* url */0][/* protocol */0]), React.createElement("input", {
                  placeholder: "Write something to do",
                  size: 90,
                  type: "text",
                  value: st[/* url */0][/* protocol */0],
                  onKeyDown: dispatchOnEnter,
                  onChange: (function (evt) {
                      return Curry._1(dispatch, /* SetProtocol */Block.__(0, [evt.target.value]));
                    })
                }), React.createElement("p", undefined, "Requested hostname: " + st[/* url */0][/* hostname */1]), React.createElement("input", {
                  placeholder: "Write something to do",
                  size: 90,
                  type: "text",
                  value: st[/* url */0][/* hostname */1],
                  onKeyDown: dispatchOnEnter,
                  onChange: (function (evt) {
                      return Curry._1(dispatch, /* SetHostname */Block.__(1, [evt.target.value]));
                    })
                }), React.createElement("p", undefined, "Requested port: " + String(st[/* url */0][/* port */2])), React.createElement("input", {
                  placeholder: "Write something to do",
                  type: "text",
                  value: String(st[/* url */0][/* port */2]),
                  onKeyDown: dispatchOnEnter,
                  onChange: (function (evt) {
                      return Curry._1(dispatch, /* SetPort */Block.__(2, [Caml_format.caml_int_of_string(evt.target.value)]));
                    })
                }), React.createElement("p", undefined, "Requested page: " + st[/* url */0][/* page */3]), React.createElement("input", {
                  placeholder: "Write something to do",
                  type: "text",
                  value: st[/* url */0][/* page */3],
                  onKeyDown: dispatchOnEnter,
                  onChange: (function (evt) {
                      return Curry._1(dispatch, /* SetPage */Block.__(3, [evt.target.value]));
                    })
                }), React.createElement("p", {
                  style: {
                    fontWeight: "bold"
                  }
                }, "Request URL:   " + r), React.createElement("button", {
                  onClick: handleButtonClick
                }, "HTTP Request"), React.createElement("p", undefined, "Response to the HTTP request is: "), React.createElement("p", {
                  style: {
                    backgroundColor: "lightGrey"
                  }
                }, "\n " + match[0][/* req_response */0]));
}

var make = Component;

exports.http_req = http_req;
exports.make = make;
/* react Not a pure module */
