import { useEffect, useState } from "react";
import "./App.css";

export default function App() {
  const [board, setBoard] = useState(Array(16).fill(0));
  const [gameId, setGameId] = useState(null);

  async function initGame() {
    const res = await fetch("http://localhost:8080/game/init", {
      method: "POST"
    });

    const data = await res.json();

    setBoard(data.board);
    setGameId(data.gameId);
  }

  async function move(direction) {
    if (!gameId) return;

    const res = await fetch("http://localhost:8080/game/step", {
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify({
        gameId,
        direction
      })
    });

    const data = await res.json();

    setBoard(data.board);

    if (data.status === 1) {
      alert("Game over");
    }
  }

  useEffect(() => {
    initGame();
  }, []);

  useEffect(() => {
    const handler = (e) => {
      switch (e.key) {
        case "ArrowUp":
        case "w":
          move("UP");
          break;

        case "ArrowDown":
        case "s":
          move("DOWN");
          break;

        case "ArrowLeft":
        case "a":
          move("LEFT");
          break;

        case "ArrowRight":
        case "d":
          move("RIGHT");
          break;

        default:
          return;
      }
    };

    window.addEventListener("keydown", handler);

    return () => {
      window.removeEventListener("keydown", handler);
    };
  }, [gameId]);

  return (
    <div className="app">
      <h1>2048</h1>

      <div className="grid">
        {board.map((value, index) => {
          const x = index % 4;
          const y = Math.floor(index / 4);

          return (
            <div
              key={index}
              className={`tile value-${value}`}
              style={{
                gridColumn: x + 1,
                gridRow: 4 - y // Flips the Y axis visually
              }}
            >
              {value === 0 ? "" : value}
            </div>
          );
        })}
      </div>

      <button onClick={initGame}>
        New Game
      </button>
    </div>
  );
}