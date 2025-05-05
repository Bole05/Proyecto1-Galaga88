// Game.cpp
#include "Game.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <resource_dir.h> 

Game::Game()
    : gameState(MENU)
    , menuTexture{}
    , backgroundTexture{}
    , bossBackgroundTexture{}
    , playerTexture{}
    , enemyTexture{}
    , bossTexture{}
    , PlyBulletText{}
    , score(0)
    , bestScore(0)
    , bossActive(false)
    , backgroundOffset(0.0f)
    , backgroundSpeed(2.0f)
    , bgTransitionActive(false)
    , bgAlpha(0.0f)
    , bgFadeSpeed(0.05f)
    , bossBgOffset(0.0f)
    , bossBgSpeed(1.5f)
    , formationOffsetX(0.0f)
    , formationDir(1.0f)
    , formationSpeed(60.0f)
{
    playerBullets.resize(MAX_BULLETS);
    enemyBullets.resize(MAX_ENEMY_BULLETS);
    bossBullets.resize(MAX_BOSS_BULLETS);
}


Game::~Game() {
 
    UnloadTexture(menuTexture);
    UnloadTexture(backgroundTexture);
    UnloadTexture(playerTexture);
    UnloadTexture(enemyTexture);
    UnloadTexture(bossTexture);
    UnloadTexture(PlyBulletText);

    CloseWindow();
}

void Game::Init() {
   
    SearchAndSetResourceDir("resources");

    srand((unsigned int)time(nullptr));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Galaga 88 - Raylib");
    SetTargetFPS(90);

   
    {
        // Menú
        Image menuImg = LoadImage("menu inicial.jpg");
        ImageResize(&menuImg, SCREEN_WIDTH, SCREEN_HEIGHT);
        menuTexture = LoadTextureFromImage(menuImg);
        UnloadImage(menuImg);

        // Fondo
        Image bgImg = LoadImage("fonda galaga fabricas.png");
        ImageResize(&bgImg, SCREEN_WIDTH, SCREEN_HEIGHT);
        backgroundTexture = LoadTextureFromImage(bgImg);
        UnloadImage(bgImg);

        Image bossBgImg = LoadImage("NIVELL_BOSS_1.png");
        TraceLog(LOG_INFO, "cargando fondo Boss  w=%d  h=%d", bossBgImg.width, bossBgImg.height);
        ImageResize(&bossBgImg, SCREEN_WIDTH, SCREEN_HEIGHT);
        bossBackgroundTexture = LoadTextureFromImage(bossBgImg);
        TraceLog(LOG_INFO, "ID textura Boss = %u", bossBackgroundTexture.id);
        UnloadImage(bossBgImg);

        /* ---------- Parámetros del fundido ---------- */
        bgTransitionActive = false;
        bgAlpha = 0.0f;   // opacidad inicial
        bgFadeSpeed = 0.05f;
        bossBgOffset = 0.0f;
        bossBgSpeed = 1.5f;

        // Player
        Image playerImg = LoadImage("99809.png");
        // Por si quieres redimensionar a 40x40
        ImageResize(&playerImg, 75, 75);
        playerTexture = LoadTextureFromImage(playerImg);
        UnloadImage(playerImg);
       
        
        // Enemy
        Image enemyImg = LoadImage("fff.png");
        ImageResize(&enemyImg, 40, 40);
        enemyTexture = LoadTextureFromImage(enemyImg);
        UnloadImage(enemyImg);

         //Boss
         Image bossImg = LoadImage("Arcade_-_Galaga_Arrangement_-_King_Galaspark-removebg-preview.png");
         ImageResize(&bossImg, 100, 100);
         bossTexture = LoadTextureFromImage(bossImg);
         UnloadImage(bossImg);
         boss.SetTexture(bossTexture);

         //bullet Player
    
         Image pBulletImg = LoadImage("Galaga88_Sprite_Ampliado-removebg-preview.png");
         ImageResize(&pBulletImg, 46, 40);              // tamaño final de la bala
         Texture2D playerBulletTex = LoadTextureFromImage(pBulletImg);
         UnloadImage(pBulletImg);

         // la misma textura para todas las balas del jugador
         for (auto& b : playerBullets)  
             b.SetTexture(playerBulletTex);

    }

    player.Init();
    boss.Init();
    InitEnemies();
}

void Game::InitEnemies() {
    enemies.clear();
    enemies.resize(MAX_ENEMIES);
    for (auto& e : enemies) {
        e.Init();
    }
}

void Game::Update() {
    float delta = GetFrameTime();
    if (WindowShouldClose()) {
        gameState = GAMEOVER;
    }
    backgroundOffset += backgroundSpeed;
    if (backgroundOffset >= backgroundTexture.height) {
        backgroundOffset = 0.0f;
    }


    switch (gameState) {
    case MENU:
        if (IsKeyPressed(KEY_ENTER)) {
            gameState = LEVEL1;
            score = 0;
            player.Init();
            boss.Init();
            InitEnemies();
        }
        break;

    case LEVEL1:
    case LEVEL2:
        formationOffsetX += formationDir * formationSpeed * GetFrameTime();
        if (formationOffsetX < -40.0f || formationOffsetX > 40.0f)  // rebote
            formationDir *= -1.0f;
        player.Update();

        // Player dispara
        if (IsKeyPressed(KEY_SPACE)) {
            for (auto& pb : playerBullets) {
                if (!pb.IsActive()) {
                    Rectangle pr = player.GetRect();
                    Vector2 pos{ pr.x + pr.width / 2 - 5, pr.y };
                    pb.Activate(pos);
                    break;
                }
            }
        }

        // Actualizar balas player
        for (auto& pb : playerBullets) {
            pb.Update();
        }
       

        // Enemigos
        UpdateEnemies();
        EnemyAttack();

        // Balas de Enemigos
        for (auto& eb : enemyBullets) {
            if (eb.IsActive()) {
                Rectangle r = eb.GetRect();
                r.y += ENEMY_BULLET_SPEED;
                eb.SetRect(r);

                if (r.y > SCREEN_HEIGHT) {
                    eb.Deactivate();
                }

                if (CheckCollisionRecs(r, player.GetRect())) {
                    eb.Deactivate();
                    player.TakeDamage();
                    if (player.GetLives() <= 0) {
                        gameState = GAMEOVER;
                    }
                }
            }
        }

        // Si matamos a todos -> Boss
        CheckAllEnemiesDefeated();
        if (gameState == BOSS) {
            bossActive = true;
            boss.Init();
            boss.Activate(true);
        }
        break;
    
    case BOSS: {
        player.Update();

        boss.Update();
        //player.Update();
        //boss.Update();
        if (IsKeyPressed(KEY_SPACE)) {
            for (auto& pb : playerBullets) {
                if (!pb.IsActive()) {
                    Rectangle pr = player.GetRect();
                    Vector2 pos{ pr.x + pr.width / 2 - 5, pr.y };
                    pb.Activate(pos);
                    break;
                }
            }
        }
        for (auto& pb : playerBullets) {
            pb.Update();
        }

        // Boss
        boss.Update();
        BossAttack();

        // Balas del Boss
        for (auto& bb : bossBullets) {
            if (bb.IsActive()) {
                Rectangle r = bb.GetRect();
                r.y += BOSS_BULLET_SPEED;
                bb.SetRect(r);

                if (r.y > SCREEN_HEIGHT) {
                    bb.Deactivate();
                }

                if (CheckCollisionRecs(r, player.GetRect())) {
                    bb.Deactivate();
                    player.TakeDamage();
                    if (player.GetLives() <= 0) {
                        gameState = GAMEOVER;
                    }
                }
            }
        }

        // Colisión de las balas del Player con el Boss
        for (auto& pb : playerBullets) {
            if (pb.IsActive() && boss.IsActive()) {
                if (CheckCollisionRecs(pb.GetRect(), boss.GetRect())) {
                    pb.Deactivate();
                    boss.TakeDamage(1);
                    score += 50;
                    if (boss.GetLife() <= 0) {
                        gameState = WIN;
                    }
                }
            }
        }
    } break;

    case GAMEOVER:
    case WIN:
        // Esperar ENTER para volver a MENU
        if (IsKeyPressed(KEY_ENTER)) {
            gameState = MENU;
            for (auto& pb : playerBullets) pb.Deactivate();
            for (auto& eb : enemyBullets)  eb.Deactivate();
            for (auto& bb : bossBullets)   bb.Deactivate();
        }
        break;
    }

    if (bgTransitionActive) {
        bgAlpha += bgFadeSpeed;
        if (bgAlpha >= 1.0f) {      // cuando llega a opacidad total…
            bgAlpha = 1.0f;
            bgTransitionActive = false;
        }
        /* ?? scroll del fondo-Boss ????????????????????????????? */
        if (gameState == BOSS || bgTransitionActive)
        {
            bossBgOffset += bossBgSpeed;
            if (bossBgOffset >= bossBackgroundTexture.height)
                bossBgOffset = 0.0f;
        }

        /* ?? guardar récord cuando termina la partida ????????? */
        if ((gameState == GAMEOVER || gameState == WIN) && score > bestScore)
            bestScore = score;
    }
    if (bgTransitionActive) {
        bgAlpha += bgFadeSpeed;              // sube opacidad
        if (bgAlpha >= 0.80f) {              // llega al 80 % máx
            bgAlpha = 0.80f;                 // (ajusta si quieres 1.0f)
            bgTransitionActive = false;      // fundido terminado
        }
    }

    /*????????????????  SCROLL DEL FONDO-BOSS  ???????????*/
    if (gameState == BOSS || bgTransitionActive) {
        bossBgOffset += bossBgSpeed;                         // mueve
        if (bossBgOffset >= bossBackgroundTexture.height)    // reinicia
            bossBgOffset = 0.0f;
    }

    /*????????????????  RÉCORD DE PUNTUACIÓN  ?????????????*/
    if ((gameState == GAMEOVER || gameState == WIN) && score > bestScore)
        bestScore = score;

}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    /*???????????????? 1) FONDO NORMAL con scroll (solo si procede) ?????????????*/
    bool mostrarFondoNormal = (gameState != BOSS) || bgTransitionActive;

    if (mostrarFondoNormal) {
        int yScroll = (int)backgroundOffset % backgroundTexture.height;
        DrawTexture(backgroundTexture, 0, yScroll, WHITE);
        DrawTexture(backgroundTexture, 0,
            yScroll - backgroundTexture.height, WHITE);
    }

    /*???????????????? 2) FONDO-BOSS con scroll propio + alfa ???????????????????*/
    if (gameState == BOSS || bgTransitionActive) {
        Color tint = WHITE;
        tint.a = (unsigned char)(bgAlpha * 255);   // 0–255
        int by = (int)bossBgOffset;
        DrawTexture(bossBackgroundTexture, 0, by, tint);
        DrawTexture(bossBackgroundTexture, 0,
            by - bossBackgroundTexture.height, tint);
    }

    /*???????????????? 3) GAMEPLAY / HUD según estado ???????????????????????????*/
    switch (gameState)
    {
    case MENU:
        if (menuTexture.id) DrawTexture(menuTexture, 0, 0, WHITE);
        DrawText("GALAGA 88", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 40, WHITE);
        DrawText("Press ENTER to start", SCREEN_WIDTH / 2 - 130, SCREEN_HEIGHT / 2, 20, WHITE);
        break;

    case LEVEL1:
    case LEVEL2:
    case BOSS:
    {
        Rectangle pr = player.GetRect();
        DrawTexture(playerTexture, (int)pr.x, (int)pr.y, WHITE);

        if (gameState != BOSS)
            for (auto& e : enemies)
                if (e.IsActive())
                    DrawTexture(enemyTexture,
                        (int)e.GetRect().x, (int)e.GetRect().y, WHITE);

        if (bossActive && boss.IsActive()) {
            boss.Draw();
            DrawText(TextFormat("Boss HP: %d", boss.GetLife()),
                SCREEN_WIDTH / 2 - 50, 10, 20, RED);
        }

        for (auto& pb : playerBullets) pb.Draw();
        for (auto& eb : enemyBullets)  eb.Draw();
        for (auto& bb : bossBullets)   bb.Draw();

        DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);
        DrawText(TextFormat("Best:  %d", bestScore), 10, 35, 20, YELLOW);
        DrawText(TextFormat("Lives: %d", player.GetLives()),
            SCREEN_WIDTH - 110, 10, 20, WHITE);
        break;
    }

    case GAMEOVER:
        DrawText("GAME OVER", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 40, WHITE);
        DrawText("Press ENTER to return to MENU", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 20, WHITE);
        break;

    case WIN:
        DrawText("YOU WIN!", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 50, 40, GREEN);
        DrawText("Press ENTER to return to MENU", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 20, WHITE);
        break;
    }

    EndDrawing();
}

void Game::UpdateEnemies()
{
    /* ?? 1)  ¿Arrancamos un ataque de grupo? ????????????????? */
    bool lanzarDive = (GetRandomValue(0, 1000) < 2);   // 0,2?% frame
    bool lanzarCircle = (GetRandomValue(0, 1000) < 2);   // 0,2?%

    int  iniciados = 0;

    /* ?? 2)  Recorremos la lista ???????????????????????????? */
    for (auto& e : enemies) {
        if (!e.IsActive()) continue;

        /* aplicar desplazamiento de la formación */
      /*  if (e.GetState() == EnemyState::FORMATION)
            e.ApplyGroupOffset(formationOffsetX);*/

        /* 2?A · arrancar Dive a los primeros 4 que cumplan */
        e.SetGroupOffset(formationOffsetX);
        //if (lanzarDive && iniciados < 4 &&
        //    e.GetState() == EnemyState::FORMATION)
        //{
        //    e.StartDive();
        //    iniciados++;
        //}

        ///* 2?B · si no lanzamos Dive, prueba Circle (otros 4) */
        //if (!lanzarDive && lanzarCircle && iniciados < 4 &&
        //    e.GetState() == EnemyState::FORMATION)
        //{
        //    e.StartCircle();
        //    iniciados++;
        //}
        if (e.GetState() == EnemyState::FORMATION) {
            if (lanzarDive && iniciados < 4) { e.StartDive();   iniciados++; }
            else if (!lanzarDive && lanzarCircle && iniciados < 4)
            {
                e.StartCircle(); iniciados++;
            }
        }
        e.Update();

        /* colisión con balas del jugador */
        for (auto& pb : playerBullets) {
            if (pb.IsActive() && CheckCollisionRecs(pb.GetRect(), e.GetRect())) {
                pb.Deactivate();
                e.Deactivate();
                score += 10;
                break;
            }
        }
    }
}


void Game::CheckAllEnemiesDefeated() {
    bool allDead = true;
    for (auto& e : enemies) {
        if (e.IsActive()) {
            allDead = false;
            break;
        }
    }

    
    if (allDead && (gameState == LEVEL1 || gameState == LEVEL2)) {
        gameState = BOSS;   
        bossActive = true;   

      
        bgTransitionActive = true;  
        bgAlpha = 0.0f;   

        for (auto& pb : playerBullets) pb.Deactivate();
        for (auto& eb : enemyBullets)  eb.Deactivate();
        for (auto& bb : bossBullets)   bb.Deactivate();
    }
}

void Game::EnemyAttack() {
    for (auto& e : enemies) {
        if (!e.IsActive()) continue;

        if (GetRandomValue(0, 100) < 3) {  
            for (auto& eb : enemyBullets) {
                if (!eb.IsActive()) {
                    Rectangle er = e.GetRect();
                    Vector2 pos{ er.x + er.width / 2 - 5, er.y + er.height };
                    eb.Activate(pos);
                    break;
                }
            }
        }
    }
}

void Game::BossAttack() {
    if (!boss.IsActive()) return;
    // 3 balas de golpe
    if (GetRandomValue(0, 100) < 5) {
        int count = 0;
        for (auto& bb : bossBullets) {
            if (!bb.IsActive()) {
                Rectangle br = boss.GetRect();
                Vector2 pos{ br.x + br.width / 2 - 5, br.y + br.height };
                bb.Activate(pos);
                count++;
                if (count >= 3) break; // 3 balas
            }
        }
    }
}
