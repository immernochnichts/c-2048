package in.random.game2048.dto;

public record GameResponse(
        String gameId,
        int[] board,
        int status
) {}
