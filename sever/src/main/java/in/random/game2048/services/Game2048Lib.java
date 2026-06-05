package in.random.game2048.services;

import com.sun.jna.Library;
import com.sun.jna.Native;

public interface Game2048Lib extends Library
{
    Game2048Lib INSTANCE =
            Native.load("game2048", Game2048Lib.class);

    int api_step(int[] board, int direction);
    void api_init(int[] board);
}
