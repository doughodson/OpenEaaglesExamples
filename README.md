
OpenEaagles Examples
====================

The most current version of OpenEaagles can be found at
[www.OpenEaagles.org][1].

Notes
-----

*  Use makeEdl.bat to generate the example *.edl files under windows, and
   use 'make edl' to generate the *.edl files under linux.


Demonstration Applications
--------------------------

* demoEfis -- demo of an electronic flight instrument system

* demoFlightDisplays1 -- demo of flight displays

* demoFlightDisplays2 -- demo of flight displays

* demoInstruments -- Instrument library demo program
    1. Contains several test instrument pages
    2. Use 'n' and 'p' (next and previous) to move between pages
    3. Use ESC to exit

* demoSubDisplays -- Quad subdisplay version of the Instrument Library demo program
    1. Contains 4 subdisplays, each containing the instrument lib demo
    2. See demoInstruments

Example Applications
--------------------

* mainCockpit -- Simple flight simulator

* mainGndMapRdr -- ground mapping radar example

* mainLaero -- demostrates flight navigation

* mainNonRT1 -- executes a simulation as fast as possible (not real-time, no concern about wall clock)

* mainPuzzle1 -- puzzle problem solver (Moves 2x2 block to first row, center position)

* mainPuzzle2 -- puzzle problem solver (15 block puzzle)

* mainQt1 -- illustrates how to interface Qt graphics with an oe simulation

* mainSim1 -- presents the simpest full-featured simulation that can be built with and only with oe classes.

* mainSim2 -- same as mainSim1 except the vehicle can be flown with a joystick and supports the JSBSim model

* mainSim3 -- simulation that display all players on a map

* mainTerrain -- draws terrain elevation data

* mainUbf1 -- A version of 'mainCockpit' that uses UBF behaviors to 'fly' an aircraft

Example GUI Applications
------------------------

* mainGlut -- Opens a GLUT window and draws a pattern.

* mainQt1 -- Opens a Qt GUI window and display all players on a map within a simulation

Test Applications
-----------------

* testDafif -- exercises DAFIF library capabilities

* testEvents -- exercises Component class send() methods

* testGraphics -- exercises graphic class available in 'graphics' library
    1. Contains several test MFD pages with common background graphics
    2. Use 'n' and 'p' (next and previous) to move between pages
    3. OpenGL selection test: use cursor and left mouse button to select a graphic item.  The selected item will flash.
    4. Use ESC to exit

* testInfrared -- general IR test program

* testIoHandler -- exercises I/O classes (i.e., i/o device library)

* testLinearSys

* testMatrix -- exercies Matrix class functionality

* testMetaObject -- exercises meta-object functionality

* testNavUtils -- extensive set of navigation test routines

* testNetHandler -- tests the network handlers (derived from NetHandler).  Includes client and server side tests/examples for the UDP, TCP, broadcast, and multicast handlers.

* testRadar -- general radar test program

* testRecordData -- variation of 'mainy1' that has a DataRecorder attached and records a data file that can be read by 'testRecordRead'.

* testRecorderRead -- reads and prints recorder data streams or binary files. Can be used with 'testRecordData' or 'testRecorderWrite'.

* testRecorderWrite -- write test data recorder files.

* testRng -- random number generator and distribution test program

* testStateMach -- example and test of state machine class

* testTables -- collection of Table tests programs

* testTemplates -- a bit of a playground for testing templates

* testTimer -- tests the functionality of the Timer class.

* testUnits  -- temporary location for misc docs for how unit conversions were tested

Tutorial applications:
--------------------------------------------------------------------------------------------

* tutorial01 -- This example demonstrates a simple compile and link with the OpenEaagles basic foundation library. It was created primary as a simple demonstration of linking to a single OpenEaagles library. The intent is to show how to build your first "Hello World" OpenEaagles-based application.

* tutorial02 -- This example demonstrates the creation of an OpenEaagles compliant class called Random. As with most extensible frameworks, macros are used to spell out the boilerplate code that needs to be defined in order to create a "well defined" class. The macros make it easy to develop native toolkit components quickly. This example purposely focuses on a simple class so that the developer can focus on the boilerplate aspects of OpenEaagles classes.

* tutorial03 -- This example extends the capability of the Random class from tutorial02. The application has been enhanced so that it can read an input file and have the native toolkit parser create the Random class with attributes specified at run-time. This example is focused as a starting point for understanding how to use the OpenEaagles parser and input language.

* tutorial04 -- tutorial03 has been enhanced so that the Random class can provide numbers drawn from different distributions. Two specific distributions have been added: uniform and exponential. The Random class has been redefined to be abstract.

* tutorial05 -- This tutorial creates a class called MyObj that can process several types of inputs. Specifically it understands a list of colors and a vector.

* tutorial06 -- This tutorial presents the construction of a very simple component called MyComp. MyComp only understands one attribute called "str". Because MyComp is built off of component, MyComp can also manage a list of pairs (a pairstream) where each Pair contains another component. This list of pairs (the pairstream) is our components container.

* tutorial07 -- Simple graphics application.

* tutorial08 -- Slightly more complicated graphics application that demonstrates multiple pages of graphics.


Libraries: (the 'x' in library name indicates eXample)
--------------------------------------------------------------------------------------------
* xBehaviors -- eXample UBF behaviors

* xPanel -- eXample components to display an instrument panel, used by 'mainy1', 'mainUbf1' and 'testRecordData'

* xRecorder -- eXample extension of the Data Recorder

* xZeroMQHandlers -- eXample ZeroMQ network handlers


[1]: http://www.OpenEaagles.org
