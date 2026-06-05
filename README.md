# 2048

A simple implementation of the classic 2048 game built with a React frontend, a Spring Boot backend, and a native C game engine accessed through JNA.

## Architecture

```
React (Frontend)
       |
       v
Spring Boot (REST API)
       |
       v
      JNA
       |
       v
C Game Engine
```

The frontend is responsible for rendering the board and handling user input.

The backend exposes a REST API that manages game sessions and delegates game logic to the native library. The only interesting part of the server is the JNA integration with a native windows DLL.

The core game mechanics are implemented in C because C is beautiful. All this boring ass web boilerplate is for creating a nice UI for the 2d array that's calculated in C code.

## Running the Project

### Backend

Build the native library:

```bash
x86_64-w64-mingw32-gcc -shared -o game2048.dll main.c grid.c
```
Then put it into resources folder and start the Spring Boot application:

```bash
mvn spring-boot:run
```

### Frontend

Install dependencies:

```bash
npm install
```

Start the development server:

```bash
npm run dev
```

The frontend will be available at (this is important because the cross-origin-whatever-the-fuck is hardcoded on the server side):

```
http://localhost:5173
```

## Notes

The native library must match the architecture of the JVM.

For example:

* 64-bit JVM → 64-bit DLL
* 32-bit JVM → 32-bit DLL
