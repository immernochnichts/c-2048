package in.random.game2048.dto;

import in.random.game2048.enums.Direction;

public record StepRequest(
        String gameId,
        Direction direction
) {}
