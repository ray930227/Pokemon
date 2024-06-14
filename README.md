基本操作
--------------
上下左右：用來控制主角的移動方向，也可以用來在各種選單介面裡做選擇。

確認鍵：Z或者Enter：用來確認選擇、進行對話。

選單操作：Z鍵用來打開選單，X鍵用來關閉選單，請注意，當選單中有"離開"選項時，使用上下移動到"離開"選項，再按Z不是X。


Debug Mode
----------------
移動速度:在靜止的時候使用按A來切換，按一次變快，再按一次變原本的速度。

遭遇野生神奇寶貝:在靜止的時候使用按S來切換，按一次不遇怪，再按一次遇怪。

超強隊伍:在靜止的時候使用按D，背包內神奇寶貝會全部變成滿等神獸。

注意事項
------
請調整/PTSD/include/condfig.hpp裡的TITLE、WINDOW_WIDTH以及WINDOW_HEIGHT以達到最佳遊玩體驗 ，調整方式如下:


```C++
constexpr const char *TITLE = "Pokemon";

constexpr unsigned int WINDOW_WIDTH = 720;
constexpr unsigned int WINDOW_HEIGHT = 720;
```