package in.random.game2048.services;

import in.random.game2048.dto.GameResponse;
import in.random.game2048.enums.Direction;
import in.random.game2048.dto.GameState;
import org.springframework.stereotype.Service;

import java.util.Arrays;
import java.util.Map;
import java.util.UUID;
import java.util.concurrent.ConcurrentHashMap;

@Service
public class GameService {

    private final Map<String, GameState> games =
            new ConcurrentHashMap<>();

    public GameResponse initialize() {

        String gameId = UUID.randomUUID().toString();

        int[] board = new int[16];

        Game2048Lib.INSTANCE.api_init(board);

        games.put(
                gameId,
                new GameState(board)
        );

        return new GameResponse(
                gameId,
                board.clone(),
                0
        );
    }

    public GameResponse step(
            String gameId,
            Direction dir
    ) {

        GameState game = games.get(gameId);

        if (game == null) {
            throw new IllegalArgumentException(
                    "Game not found: " + gameId
            );
        }

        int[] board = game.board();

        int status = switch (dir) {
            case RIGHT -> Game2048Lib.INSTANCE.api_step(board, 0);
            case UP    -> Game2048Lib.INSTANCE.api_step(board, 1);
            case LEFT  -> Game2048Lib.INSTANCE.api_step(board, 2);
            case DOWN  -> Game2048Lib.INSTANCE.api_step(board, 3);
        };

        return new GameResponse(
                gameId,
                board.clone(),
                status
        );
    }

    public GameResponse reset(String gameId) {

        GameState game = games.get(gameId);

        if (game == null) {
            throw new IllegalArgumentException(
                    "Game not found: " + gameId
            );
        }

        int[] board = game.board();

        Arrays.fill(board, 0);

        Game2048Lib.INSTANCE.api_init(board);

        return new GameResponse(
                gameId,
                board.clone(),
                0
        );
    }

    public void delete(String gameId) {
        games.remove(gameId);
    }
}