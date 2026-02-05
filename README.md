# YtUINavigation





## setup

Make your GameInstance class inherit from the class  `UYtUIGameInstance`



in GameInstance Blueprint class, config all menu widget blueprint

![Snipaste_2026-01-05_23-38-45](./img/Snipaste_2026-01-05_23-38-45.png)



in level `HUD`,  call `Register Widgets`



![](./img/Snipaste_2026-01-05_23-38-17.png)

![](./img/Snipaste_2026-02-02_19-45-05.png)



![Snipaste_2026-02-02_19-45-40](./img/Snipaste_2026-02-02_19-45-40.png)

![Snipaste_2026-02-02_19-45-44](./img/Snipaste_2026-02-02_19-45-44.png)



## use ui navigation

```c++

UFUNCTION(BlueprintCallable)
UUserWidget* ShowScreen(EUIScreen ScreenId); // Replace current (clear stack), like HUD

UFUNCTION(BlueprintCallable)
UUserWidget* PushScreen(EUIScreen ScreenId); // Push onto stack

UFUNCTION(BlueprintCallable)
void PopScreen(); // Pop top and show previous

```





## use global style



You can apply a consistent UI style throughout the entire project.



create DataAsset

![](./img/Snipaste_2026-02-02_19-51-16.png)



select `UIStyle Data`

![](./img/Snipaste_2026-02-02_19-50-57.png)

![Snipaste_2026-02-02_19-49-50](./img/Snipaste_2026-02-02_19-49-50.png)





Set the parent class of the Widget Blueprint to `UYtBaseWidget` .



![](./img/Snipaste_2026-02-02_19-57-57.png)

![](./img/Snipaste_2026-02-02_19-48-41.png)



set `Designer Style Data`；



If the current widget does not want to use the global style, uncheck **Use Designer Style**. Otherwise, the “GlobalUIStyle” will override the current widget.



![](./img/Snipaste_2026-02-02_19-52-29.png)



