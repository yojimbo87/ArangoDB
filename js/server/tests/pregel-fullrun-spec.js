/*jslint indent: 2, nomen: true, maxlen: 120, todo: true, white: false, sloppy: false */
/*global require, describe, beforeEach, it, expect, spyOn, createSpy, createSpyObj, afterEach, runs, waitsFor */

////////////////////////////////////////////////////////////////////////////////
/// @brief test a complete run through pregel's algorithm
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2010-2014 triagens GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Florian Bartels, Michael Hackstein
/// @author Copyright 2014, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

var conductor = require("org/arangodb/pregel").Conductor;
var graph = require("org/arangodb/general-graph");

describe("Full Pregel execution", function () {
  "use strict";

  describe("a small unsharded graph", function () {

    var gN, v, e, g;

    beforeEach(function () {
      gN = "UnitTestPregelGraph";
      v = "UnitTestVertices";
      e = "UnitTestEdges";

      if (graph._exists(gN)) {
        graph._drop(gN, true);
      }
      g = graph._create(
        gN,
        [graph._undirectedRelation(e, [v])]
      );

      var saveVertex = function (key) {
        g[v].save({_key: String(key)});
      };

      var saveEdge = function (from, to) {
        g[e].save(v + "/" + from, v + "/" + to, {});
      };

      var i;
      for (i = 0; i < 14; i++) {
        saveVertex(i);
      }
      saveEdge(1, 3);
      saveEdge(2, 1);
      saveEdge(2, 5);
      saveEdge(4, 3);
      saveEdge(4, 2);
      saveEdge(6, 7);
      saveEdge(8, 7);
      saveEdge(9, 10);
      saveEdge(10, 11);
      saveEdge(11, 12);
      saveEdge(12, 13);
    });

    afterEach(function () {
      graph._drop(gN, true);
    });

    it("should identify all distinct graphs", function () {
      var myPregel = function (vertex, message, global) {
        var inc = message.getMessages();
        var next;

        if (global.step === 0) {
          vertex._result = {
            inGraph: vertex._key,
            inBound: []
          };
        }
        var min = vertex._result.inGraph;
        if (global.step === 1) {
          while (inc.hasNext()) {
            next = inc.next();
            vertex._result.inBound.push(next._from);
            if (next.data < min) {
              min = next.data;
            }
          }
        } else if (global.step > 1) {
          while (inc.hasNext()) {
            next = inc.next();
            if (next.data < min) {
              min = next.data;
            }
          }
        }
        if (global.step < 2 || min < vertex._result.inGraph) {
          vertex._result.inGraph = min;
          var outBound = vertex._outEdges.map(function (e) {
            return e._to;
          });
          outBound.concat(vertex._result.inBound).forEach(function (t) {
            message.sendTo(t, vertex._result.inGraph);
            //message.sendTo();
          });
        }
        vertex._deactivate();
      };
      var id = conductor.startExecution(gN, myPregel.toString());
      require("console").log(id);
      var count = 0;
      while (count < 10) {
        require("internal").wait(1);
        if (conductor.getInfo(id).state === "finished") {
          count = 2000;
          break;
        }
        count++;
      }
      expect(count).toEqual(2000);
    });


  });

});

