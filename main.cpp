#include <Novice.h>
#include<Vector2.h>

const char kWindowTitle[] = "GC1D_07_タカブ_コウキ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	const int kWindowWidth = 1280; // ウィンドウの横幅
	const int kWindowHeight = 720; // ウィンドウの縦幅
	int playerSpeed = 5;
	//int fiftycoin = 50;//50コイン
	//    int faivcoin = 5;//5コイン

	struct Ball {
		Vector2 position;
		Vector2 velocity;
		Vector2 acceleration;
		float radius;
		unsigned int color;
	};

	Ball ball = {
		{10.0f,50.0f},
		{0.0f,0.0f},
		{0.0f,-0.8f},
		50.0f,
		WHITE
	};
	
	float positionY = 0;
	positionY += -100;
	positionY *= -1;

	float screenPos = 0.0f;
	//
	// 背景の変数の初期化
	//
	int stageHeight = kWindowHeight;
	//ゲーム中の背景画像の座標
	int ScreenX1 = 0;
	int ScreenPosY1 = 0;

	//ゲーム中の背景画像の座標2.1
	int ScreenX2 = 0;
	int ScreenPosY2 = ScreenPosY1 + stageHeight;

	//ゲーム中の背景画像の座標2.2
	int ScreenX2_2 = 0;
	int ScreenPosY2_2 = ScreenPosY2 + stageHeight;

	//ゲーム中の背景画像の座標2.2
	int ScreenX2_3 = 0;
	int ScreenPosY2_3 = ScreenPosY2_2 + stageHeight;

	//ゲーム中の背景画像の座標3
	int ScreenX3 = 0;
	int ScreenPosY3 = ScreenPosY2_3 + stageHeight;

	//ゲーム中の背景画像の座標4
	int ScreenX4 = 0;
	int ScreenPosY4 = ScreenPosY3 + stageHeight;

	int stageSpeedY = 1;//背景のスクロールスピード
	enum Scene {
		TITLE,
		GAME,
		CLEAR,
		OVER,
	};

	int scene = TITLE;

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);


	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		///
		switch (scene) {
		case TITLE:
			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == 0) {
				scene = GAME;
			}
			break;
		case GAME:
		///プレイヤーの移動
		ball.position.x = ball.position.x + playerSpeed;//右に
		if (keys[DIK_SPACE] != 0 && ball.position.y == ball.radius) {
			
			ball.velocity.y = 20.0f;//ジャンプ
			//PlayerSpeedY = 10;
		}

		ball.velocity.y += ball.acceleration.y;
		ball.position.y += ball.velocity.y;

		//地面にめり込まないようにする処理
		if (ball.position.y <= ball.radius) {
			ball.position.y = ball.radius;
		}


		screenPos = (ball.position.y + -500) * -1;//2フレーム後にpositionYが変化しないようにする変数

		//背景の更新処理
		if (ScreenPosY4 != 0) {
			//背景のスクロール
			ScreenPosY1 -= stageSpeedY;
			ScreenPosY2 -= stageSpeedY;
			ScreenPosY2_2 -= stageSpeedY;
			ScreenPosY2_3 -= stageSpeedY;
			ScreenPosY3 -= stageSpeedY;
			ScreenPosY4 -= stageSpeedY;
		}
		

		break;
		case OVER:
			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == 0) {
				scene = TITLE;
			}
			break;

		case CLEAR:
			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == 0) {
				scene = TITLE;
			}
			break;
		}


		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		//Novice::DrawEllipse(playerPosX, playerPosY, playerRadius, playerRadius, 0.0f, WHITE,kFillModeSolid);
		Novice::DrawEllipse((int)ball.position.x, (int)screenPos, (int)ball.radius, (int)ball.radius, 0.0f, WHITE, kFillModeSolid);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
