package in.random.game2048.controllers;

import in.random.game2048.dto.GameResponse;
import in.random.game2048.dto.ResetRequest;
import in.random.game2048.dto.StepRequest;
import in.random.game2048.services.GameService;
import org.springframework.web.bind.annotation.*;

@CrossOrigin(origins = "http://localhost:5173")
@RestController
@RequestMapping("/game")
public class GameController {

    private final GameService gameService;

    public GameController(GameService gameService) {
        this.gameService = gameService;
    }
    
    @GetMapping("/")
    public String index()
    {
        return "bullshit works";
    }

    @PostMapping("/init")
    public GameResponse init() {
        System.out.println("init reached");
        return gameService.initialize();
    }

    @PostMapping("/step")
    public GameResponse step(@RequestBody StepRequest request) {
        System.out.println("step reached");
        return gameService.step(
                request.gameId(),
                request.direction()
        );
    }

    @PostMapping("/reset")
    public GameResponse reset(@RequestBody ResetRequest request) {
        System.out.println("reset reached");
        return gameService.reset(
                request.gameId()
        );
    }
}