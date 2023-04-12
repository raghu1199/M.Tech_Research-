//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package testwireless;

//
// TODO auto-generated type
//

simple Server
{
    gates:
        input in @directIn;
}
network Wireless
{
    @display("bgb=757,435");
    submodules:
        server: Server {
            @display("p=27,40");
        }
        node1: Node {
            @display("p=56,133");
        }
        node2: Node {
            @display("p=148,211");
        }
        node3: Node {
            @display("p=148,40");
        }
        node4: Node {
            @display("p=336,361");
        }
        node5: Node {
            @display("p=336,250");
        }
        node6: Node {
            @display("p=336,101");
        }
        node7: Node {
            @display("p=336,19");
        }
        node8: Node {
            @display("p=555,394");
        }
        node9: Node {
            @display("p=555,322");
        }
        node10: Node {
            @display("p=575,225");
        }
        node11: Node {
            @display("p=575,154");
        }
        node12: Node {
            @display("p=544,58");
        }
}
simple Node
{
    gates:
        input in @directIn;
}

