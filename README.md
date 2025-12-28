[![build-and-release](https://github.com/just-geniuss/plane_game/actions/workflows/build-release.yml/badge.svg)](https://github.com/just-geniuss/plane_game/actions/workflows/build-release.yml)

# Space Shooter (SFML)

Небольшой вертикальный скролл‑шутер на C++17 и SFML 2.5+. Проект кроссплатформенный (Windows/Linux/macOS), включает главное меню, игру, паузу, настройки и таблицу рекордов.

## Требования
- CMake 3.16+
- Компилятор с поддержкой C++17 (MSVC, clang, g++)
- SFML 2.5+ (graphics, window, system, audio)

## Установка SFML
### Windows (MSVC + vcpkg)
1. Установите [vcpkg](https://github.com/microsoft/vcpkg).
2. `vcpkg install sfml`
3. Запускайте CMake с `-DCMAKE_TOOLCHAIN_FILE="<путь>/vcpkg/scripts/buildsystems/vcpkg.cmake"`.

### Windows (ручная установка)
1. Скачайте бинарники SFML с https://www.sfml-dev.org/download.php (версия под ваш компилятор).
2. Распакуйте, добавьте путь к `SFMLConfig.cmake` в `CMAKE_PREFIX_PATH`.

### Ubuntu / Debian
```bash
sudo apt update
sudo apt install libsfml-dev
```

### macOS (Homebrew)
```bash
brew install sfml
```

## Сборка
```bash
cmake -S . -B build
cmake --build build
```
Запуск:
```bash
./build/spaceshooter
```

## Структура папок
- CMakeLists.txt — основной CMake
- src/, include/ — исходный код (ядро, состояния, логика игры, UI, системы)
- assets/
  - config/ — настройки (`settings.ini`), рекорды (`highscores.txt`)
  - textures/, fonts/, sounds/, shaders/ — ассеты (положите свои файлы; сейчас лежат заглушки)

## Основные классы
- core/Game — окно, цикл, ресурсы, состояния
- core/Settings — загрузка/сохранение настроек, привязки клавиш
- states/* — MainMenu, Gameplay, Pause, Settings, HighScore, GameOver
- game/* — сущности: Player, Enemy, Bullet, PowerUp, WaveSystem, Explosion
- systems/HighScoreSystem — загрузка/сохранение топа
- ui/* — Button, HUD

## Управление по умолчанию
- Движение: A/D/W/S
- Стрельба: Space
- Пауза: Esc

Изменить можно в `assets/config/settings.ini` или в меню настроек (VSync, громкость музыки). Клавиши хранятся в ini: `key_Action=KeyName`.

## Ассеты
В репозитории лежат только заглушки `.gitkeep`. Добавьте свои файлы:
- fonts/Default.ttf
- sounds/music.ogg, sounds/fire.wav, sounds/explosion.wav
- textures/player.png, enemy_*.png, bullet_*.png, background_*.png

Код корректно запускается и без текстур/шрифтов (UI будет упрощён, в консоль выводится предупреждение). 

Подгружены текстуры врагов. 
