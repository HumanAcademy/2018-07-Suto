#include <string>
#include "XLibrary11.hpp"
using namespace XLibrary11;

enum Mode
{
	Title,
	Rule,
	Game,
	Dragon
};

Float3 GetRandomPosition()
{
	return Float3(
		rand() / (float)RAND_MAX * App::GetWindowSize().x - App::GetWindowSize().x / 2,
		App::GetWindowSize().y / 2 + rand() / (float)RAND_MAX * 100,
		0.0
	);
}

Float3 GetRandom2Position()
{
	return Float3(
		rand() / (float)RAND_MAX * App::GetWindowSize().x - App::GetWindowSize().x / 2,
		800,
		0.0
	);
}

Float3 BossPosition()
{
	return Float3(
		0, 800, 0
	);
}

bool IsHit(
	Float3 position1,
	Float3 position2,
	float range
)
{
	if (position1.x - range < position2.x &&
		position1.x + range > position2.x &&
		position1.y - range < position2.y &&
		position1.y + range > position2.y)
	{
		return true;
	}
	return false;
}

int MAIN()
{
	Mode mode = Title;

	App::SetWindowSize(729, 1032);

	Camera camera;

	float playerSpeed = 5.0;

	Sprite player(L"player.png");
	player.scale = 0.3;
	bool playerFlag = false;

	float enemySpeed = 5.0;
	const int enemyNum = 4.0;
	int enemycount[] = { 0,1,2,3 };

	Sprite enemy(L"戦闘機01.png");
	enemy.scale = 0.1;
	int enemyFlag[] = { -1,-1,-1,-1 };

	Float3 enemyPosition[enemyNum];

	const int bulletNum = 15;
	const float bulletSpeed = 10.0;
	int bulletIndex = 0;
	int bulletInterval = 0;

	Sprite bullet(L"bullet.png");
	bullet.scale = 0.25;

	Float3 bulletPosition[bulletNum];
	float bulletRadian[bulletNum];
	bool bulletFlag = false;

	float bossSpeed = 0.5;
	const int bossNum = 1.0;
	int bosspoint = 0;

	Sprite boss(L"飛行船01.png");
	boss.scale = 0.75;
	bool bossFlag = false;
	bool bossFlag2 = false;
	int bosscount = 0;
	Float3 bossPosition[bossNum];

	const int bullet5Num = 20.0;
	float bullet5Speed = 10.0;
	int bullet5Index = 0;
	int bullet5Interval = 0;

	Sprite bullet5(L"bullet2.png");
	bullet5.scale = 0.2;

	Float3 bullet5Position[bullet5Num];
	float bullet5Radian[bullet5Num];
	int bullet5count = 0;
	bool bullet5Flag = false;

	const int misairuNum = 20.0;
	float misairuSpeed = 10.0;
	int misairuIndex = 0;
	int misairuInterval = 0;

	Sprite misairu(L"ミサイル.png");
	misairu.scale = 0.2;
	int misairucount = 0;

	Float3 misairuPosition[misairuNum];
	float misairuRadian[misairuNum];
	bool misairuFlag = false;

	const int bullet4Num = 3;
	float bullet4Speed = 10.0;
	int bullet4Index = 0;
	int bullet4Interval = 0;

	Sprite bullet4(L"大火球.png");
	bullet4.scale = 0.75;

	Float3 bullet4Position[bullet4Num];
	float bullet4Radian[bullet4Num];
	bool bullet4Flag = false;


	const int bullet2Num = 45.0;
	float bullet2Speed = 10.0;
	int bullet2Index = 0;
	int bullet2Interval = 0;

	Sprite bullet2(L"bullet2.png");
	bullet2.scale = 0.1;

	Float3 bullet2Position[bullet2Num];
	float bullet2Radian[bullet2Num];
	bool bullet2Flag = false;

	const int enemy2Num = 2.0;
	float enemy2Speed = 3.0;
	int enemy2count[] = { 0,1 };

	Sprite enemy2(L"ヘリ.png");
	enemy2.scale = 0.2;

	Float3 enemy2Position[enemy2Num];
	int enemy2Flag[] = { -1,-1 };

	Sprite propeller(L"プロペラ.png");
	propeller.scale = 0.2;
	propeller.SetPivot(Float2(
		0.0, -0.347
	));

	const int bullet3Num = 10;
	float bullet3Speed = 20.0;
	int bullet3Index = 0;
	int bullet3Interval = 0;

	Sprite bullet3(L"弾02.png");
	bullet3.scale = 0.15;

	Float3 bullet3Position[bullet3Num];
	float bullet3Radian[bullet3Num];
	bool bullet3Flag = false;

	Sprite aicon(L"アイコン＆ゲージ.png");
	aicon.scale = 0.25;
	aicon.position = Float3(
		-175, -425, 0
	);
	bool aiconFlag = false;

	Sprite bar2(L"体力ゲージ01.png");
	bar2.scale.x = 0.254;
	bar2.scale.y = 0.25;
	bar2.position = Float3(
		-254, -425.5, 0
	);
	bar2.SetPivot(Float2(
		-0.9, 0.0
	));
	bool bar2Flag = false;

	int life = 0;
	int time = 0;
	bool cooldown = false;
	int count = 0;
	int count2 = 0;

	Sprite bar4(L"ブレスゲージ01.png");
	bar4.scale.x = 0.19;
	bar4.scale.y = 0.255;
	bar4.position = Float3(
		-256, -400, 0
	);
	bar4.SetPivot(Float2(
		-0.9, 0.0
	));
	bool bar4Flag = false;

	Sprite bar5(L"ボスHP枠.png");
	bar5.scale.x = 1.7;
	bar5.scale.y = 1.0;
	bar5.position = Float3(
		0, 500, 0
	);
	bool bar5Flag = false;

	Sprite bar6(L"ボスHPゲージ.png");
	bar6.scale.x = 1.7;
	bar6.scale.y = 1.0;
	bar6.position = Float3(
		0, 550, 0
	);
	bar6.SetPivot(Float2(
		0.0, 0.0
	));
	bool bar6Flag = false;

	int bosslife = 0;
	int bosstime = 0;
	bool bosscooldown = false;

	Sprite bakuhathu(L"爆発.png");
	bakuhathu.scale = 0.2;
	Float3 bakuhathuposition[4] = {};

	Sprite bakuhathu2(L"爆発.png");
	bakuhathu2.scale = 0.3;
	Float3 bakuhathu2position[2] = {};

	Sprite bakuhathu3(L"爆発.png");
	bakuhathu3.scale = 0.75;
	bool bakuhathu3Flag = false;
	int bakuhathu3count = 0;

	Sprite bakuhathu4(L"爆発.png");
	bakuhathu4.scale = 1.25;
	bool bakuhathu4Flag = false;
	int bakuhathu4count = 0;

	Sprite bakuhathu5(L"爆発.png");
	bakuhathu5.scale = 1.75;
	bakuhathu5.position = Float3(
		0, 400, 0
	);
	bool bakuhathu5Flag = false;
	int bakuhathu5count = 0;

	int mp = 0;
	int mp2 = 0;


	bool command = true;

	Sprite title2(L"タイトル01.png");
	Sprite title(L"タイトル02.png");
	Sprite rule(L"操作方法.png");
	Sprite background(L"背景2.png");
	Sprite gameover(L"GAME OVER.png");
	Sprite gameclear(L"クリア画面.png");

	Sound BGMSound(L"kaisen.wav");
	int BGMcount = 0;

	while (App::Refresh())
	{

		camera.Update();

		switch (mode)
		{
		case Title:

			if (App::GetKeyDown(VK_UP))
			{
				command = true;
			}
			if (App::GetKeyDown(VK_DOWN))
			{
				command = false;
			}
			if (!command)
			{
				title2.Draw();
			}
			if (command)
			{
				title.Draw();
			}
			if (!command)
			{
				title2.Draw();
			}

			if (App::GetKeyDown(VK_SPACE) &&
				command)
			{
				player.position = Float3(
					0, -350, 0
				);
				enemySpeed = 5.0;
				enemy2Speed = 3.0;
				bossSpeed = 0.5;
				bar2.scale.x = 0.254;
				bar6.scale.x = 1.7;
				count = 0;
				count2 = 0;
				bosspoint = 0;
				bosscount = 0;
				bullet5count = 0;
				misairucount = 0;
				bakuhathu3count = 0;
				bakuhathu4count = 0;
				bakuhathu5count = 0;
				BGMcount = 0;
				life = 8;
				bosslife = 100;
				mp = 3;
				mp2 = 0;
				bar4.scale.x = 0.19;
				for (int t = 0; t < 4; t++)
				{
					enemycount[t] = 0;
				}

				for (int j = 0; j < 4; j++)
				{
					enemyFlag[j] = -1;
				}

				for (int r = 0; r < 2; r++)
				{
					enemycount[r] = 0;
				}

				for (int v = 0; v < 2; v++)
				{
					enemyFlag[v] = -1;
				}

				playerFlag = false;
				aiconFlag = false;
				bar2Flag = false;
				bar4Flag = false;
				bar5Flag = false;
				bar6Flag = false;
				bossFlag = false;
				bossFlag2 = false;
				bosscooldown = false;
				bulletFlag = false;
				bullet2Flag = false;
				bullet3Flag = false;
				bullet4Flag = false;
				bullet5Flag = false;
				misairuFlag = false;
				bakuhathu3Flag = false;
				bakuhathu4Flag = false;
				bakuhathu5Flag = false;
				BGMSound.Play();

				aicon.position = Float3(
					-175, -425, 0
				);

				bar2.position = Float3(
					-254, -425.5, 0
				);

				bar4.position = Float3(
					-257, -440, 0
				);

				bar5.position = Float3(
					260, 500, 0
				);

				bar6.position = Float3(
					260, 500, 0
				);

				for (int i = 0; i < enemyNum; i++)
				{
					enemyPosition[i] = GetRandomPosition();
				}

				for (int i = 0; i < enemy2Num; i++)
				{
					enemy2Position[i] = GetRandomPosition();
				}

				for (int i = 0; i < bossNum; i++)
				{
					bossPosition[i] = BossPosition();
				}

				for (int i = 0; i < bulletNum; i++)
				{
					bulletPosition[i].y = 9999.0;
					bulletRadian[i] = 0.0;
				}

				for (int i = 0; i < bullet4Num; i++)
				{
					bullet4Position[i].y = 9999.0;
					bullet4Radian[i] = 0.0;
				}

				for (int i = 0; i < bullet2Num; i++)
				{
					bullet2Position[i].y = -9999.0;
					bullet2Radian[i] = 0.0;
				}

				for (int i = 0; i < bullet5Num; i++)
				{
					bullet5Position[i].y = -9999.0;
					bullet5Radian[i] = 0.0;
				}

				for (int i = 0; i < misairuNum; i++)
				{
					misairuPosition[i].y = -9999.0;
					misairuRadian[i] = 0.0;
				}

				for (int i = 0; i < bullet3Num; i++)
				{
					bullet3Position[i].y = -9999.0;
					bullet3Radian[i] = 0.0;
				}

				mode = Game;
			}


			if (App::GetKeyDown(VK_SPACE) &&
				!command)
			{
				mode = Rule;
			}

			camera.position = 0.0;

			break;

		case Rule:

			if (App::GetKeyDown(VK_SPACE))
			{
				command = true;
				mode = Title;
			}

			rule.Draw();
			break;

		case Game:

			BGMcount++;
			if (BGMcount > 9120)
			{
				BGMcount = 0;
				BGMSound.Play();
			}

			background.Draw();

			bulletInterval++;
			if (App::GetKeyDown('J') &&
				bulletFlag == false)
			{
				if (bulletInterval > 15)
				{
					bulletInterval = 0;
					bulletPosition[bulletIndex] = Float3(
						player.position.x - 2, player.position.y + 120.0, 0.0
					);
					bulletRadian[bulletIndex] =
						0.0;

					bulletIndex++;
					if (bulletIndex >= bulletNum)
						bulletIndex = 0;
				}
			}



			for (int i = 0; i < bulletNum; i++)
			{
				bulletPosition[i] += Float3(
					sinf(bulletRadian[i]),
					cosf(bulletRadian[i]),
					0.0
				) * bulletSpeed;
				bullet.position = bulletPosition[i];
				if (bulletFlag == false)
				{
					bullet.Draw();
				}
			}

			if (App::GetKeyDown('K') &&
				bullet4Flag == false)
			{
				if (mp < 0)
				{
					mp = 0;
					bar4.scale.x = 0;
				}

				if (bar4.scale.x > 0)
				{
					bullet4Position[bullet4Index] = Float3(
						player.position.x - 5, player.position.y + 255.0, 0.0
					);
					bullet4Radian[bullet4Index] =
						0.0;

					bullet4Index++;
					if (bullet4Index >= bullet4Num)
						bullet4Index = 0;
				}
				mp--;
				bar4.scale.x -= 0.19 / 3;
			}

			if (App::GetKey('L'))
			{
				if (mp < 3)
				{
					mp2++;
					if (mp2 > 175)
					{
						mp2 = 0;
						mp++;
						bar4.scale.x += 0.19 / 3;
					}
				}
				bulletFlag = true;
				bullet4Flag = true;
			}
			if (App::GetKeyUp('L'))
			{
				bulletFlag = false;
				bullet4Flag = false;
			}

			for (int i = 0; i < enemyNum; i++)
			{
				if (enemyPosition[i].y < -App::GetWindowSize().y - 1 / 2)
				{
					enemyPosition[i] = GetRandomPosition();
				}
				enemyPosition[i] += Float3(
					0.0,
					-enemySpeed,
					0.0
				);
				enemy.position = enemyPosition[i];

				float hitRange =
					enemy.GetSize().y * 1 / 2 *
					enemy.scale.y;
				for (int j = 0; j < bulletNum; j++)
				{
					if (IsHit(
						enemyPosition[i],
						bulletPosition[j],
						hitRange
					) && enemyFlag[i] == -1)
					{
						bosspoint++;
						bakuhathuposition[i] = enemyPosition[i];
						enemyPosition[i] =
							camera.position +
							GetRandomPosition();

						bulletPosition[j] = 1000;

						enemyFlag[i] = j;
					}
					else if (enemyFlag[i] == j)
					{
						enemycount[i]++;
						if (enemycount[i] > 30)
						{
							bakuhathu.position = 1000;
							enemycount[i] = 0;
							bakuhathu.Draw();
							enemyFlag[i] = -1;
						}
						else if (enemycount[i] != 30)
						{
							bakuhathu.position = bakuhathuposition[i];
							bakuhathu.Draw();
						}
					}
					enemy.Draw();
				}

				float hitRange2 =
					enemy.GetSize().y * 1.45 *
					enemy.scale.y;
				for (int j = 0; j < bullet4Num; j++)
				{
					if (IsHit(
						enemyPosition[i],
						bullet4Position[j],
						hitRange2
					))
					{
						bosspoint++;
						enemyPosition[i] =
							camera.position +
							GetRandomPosition();
					}
				}

				bullet2Interval++;
				if (bullet2Interval > 60)
				{
					bullet2Interval = 0;
					bullet2Position[bullet2Index] = Float3(
						enemy.position.x, enemy.position.y - 50, 0.0
					);
					bullet2Radian[bullet2Index] =
						0.0;

					bullet2Index++;
					if (bullet2Index >= bullet2Num)
						bullet2Index = 0;
				}
			}

			for (int i = 0; i < bullet2Num; i++)
			{
				float hitRange =
					bullet2.GetSize().y * 1 / 2 *
					bullet2.scale.y;
				for (int j = 0; j < bulletNum; j++)
				{
					if (IsHit(
						bullet2Position[i],
						bulletPosition[j],
						hitRange
					))
					{
						bullet2Position[i] =
							camera.position +
							-10000000000000;
					}
				}

				float hitRange2 =
					bullet2.GetSize().y * 2.0 *
					bullet2.scale.y;
				for (int j = 0; j < bullet4Num; j++)
				{
					if (IsHit(
						bullet2Position[i],
						bullet4Position[j],
						hitRange2
					))
					{
						bullet2Position[i] =
							camera.position +
							-10000000000000;
					}
				}
			}

			for (int i = 0; i < enemy2Num; i++)
			{
				if (enemy2Position[i].y < -App::GetWindowSize().y - 1 / 2)
				{
					enemy2Position[i] = GetRandom2Position();
				}
				enemy2Position[0] += Float3(
					0.5,
					-enemy2Speed,
					0.0
				);
				enemy2Position[1] += Float3(
					-0.5,
					-enemy2Speed,
					0.0
				);
				enemy2.position = enemy2Position[i];

				float hitRange =
					enemy2.GetSize().y * 1 / 2 *
					enemy2.scale.y;
				enemy2.GetSize().x * 1 / 2 *
					enemy2.scale.x;
				for (int j = 0; j < bulletNum; j++)
				{
					if (IsHit(
						enemy2Position[i],
						bulletPosition[j],
						hitRange
					) && enemy2Flag[i] == -1)
					{
						bosspoint++;
						bakuhathu2position[i] = enemy2Position[i];
						enemy2Position[i] =
							GetRandom2Position();

						bulletPosition[j] = 1000;

						enemy2Flag[i] = j;
					}
					else if (enemy2Flag[i] == j)
					{
						enemy2count[i]++;
						if (enemy2count[i] > 30)
						{
							bakuhathu2.position = 1000;
							enemy2count[i] = 0;
							bakuhathu2.Draw();
							enemy2Flag[i] = -1;
						}
						else if (enemy2count[i] != 30)
						{
							bakuhathu2.position = bakuhathu2position[i];
							bakuhathu2.Draw();
						}
					}
					propeller.position = Float3(
						enemy2.position.x, enemy2.position.y - 35, 0.0);
					propeller.angles.z = (App::GetTime() * 180.0) * 3.5;

					enemy2.Draw();

					propeller.Draw();
				}

				float hitRange2 =
					enemy2.GetSize().y * 0.6 *
					enemy2.scale.y;
				for (int j = 0; j < bullet4Num; j++)
				{
					if (IsHit(
						enemy2Position[i],
						bullet4Position[j],
						hitRange2
					))
					{
						bosspoint++;
						enemy2Position[i] =
							GetRandom2Position();
					}
				}

				bullet3Interval++;
				if (bullet3Interval > 10)
				{
					bullet3Interval = 0;
					bullet3Position[bullet3Index] = Float3(
						enemy2.position.x, enemy2.position.y - 90, 0
					);

					bullet3Radian[bullet3Index] =
						0.0;

					bullet3Index++;
					if (bullet3Index >= bullet3Num)
						bullet3Index = 0;
				}
			}

			for (int i = 0; i < bullet3Num; i++)
			{
				float hitRange =
					bullet3.GetSize().y * 1 / 2 *
					bullet3.scale.y;
				for (int j = 0; j < bulletNum; j++)
				{
					if (IsHit(
						bullet3Position[i],
						bulletPosition[j],
						hitRange
					))
					{
						bullet3Position[i] =
							camera.position +
							-10000000000000;
					}
				}

				float hitRange2 =
					bullet3.GetSize().y * 1.5 *
					bullet3.scale.y;
				for (int j = 0; j < bullet4Num; j++)
				{
					if (IsHit(
						bullet3Position[i],
						bullet4Position[j],
						hitRange2
					))
					{
						bullet3Position[i] =
							camera.position +
							-10000000000000;
					}
				}
			}

			for (int i = 0; i < bullet2Num; i++)
			{
				bullet2Position[i] -= Float3(
					sinf(bullet2Radian[i]),
					cosf(bullet2Radian[i]),
					0.0
				) * bullet2Speed;
				bullet2.position = bullet2Position[i];

				if (bullet2Flag == false)
				{
					bullet2.Draw();
				}
			}

			for (int i = 0; i < bullet5Num; i++)
			{
				bullet5Position[i] -= Float3(
					sinf(bullet5Radian[i]),
					cosf(bullet5Radian[i]),
					0.0
				) * bullet5Speed;
				bullet5.position = bullet5Position[i];

				if (bullet5Flag == false)
				{
					bullet5.Draw();
				}
			}

			for (int i = 0; i < misairuNum; i++)
			{
				misairuPosition[i] -= Float3(
					sinf(misairuRadian[i]),
					cosf(misairuRadian[i]),
					0.0
				) * misairuSpeed;
				misairu.position = misairuPosition[i];

				if (misairuFlag == false)
				{
					misairu.Draw();
				}
			}

			for (int i = 0; i < bullet3Num; i++)
			{
				bullet3Position[i] -= Float3(
					sinf(bullet3Radian[i]),
					cosf(bullet3Radian[i]),
					0.0
				) * bullet3Speed;
				bullet3.position = bullet3Position[i];

				if (bullet3Flag == false)
				{
					bullet3.Draw();
				}
			}

			if (App::GetKey('D'))
				player.position.x += playerSpeed;

			if (App::GetKey('A'))
				player.position.x -= playerSpeed;

			if (App::GetKey('W'))
				player.position.y += playerSpeed;

			if (App::GetKey('S'))
				player.position.y -= playerSpeed;

			if (player.position.x > App::GetWindowSize().x / 2 + 5)
				player.position.x = App::GetWindowSize().x / 2 + 5;

			if (player.position.x < -App::GetWindowSize().x / 2 - 5)
				player.position.x = -App::GetWindowSize().x / 2 - 5;

			if (player.position.y > App::GetWindowSize().y / 2 + 5)
				player.position.y = App::GetWindowSize().y / 2 + 5;

			if (player.position.y < -App::GetWindowSize().y / 2 - 5)
				player.position.y = -App::GetWindowSize().y / 2 - 5;

			if (playerFlag == false)
			{
				player.Draw();
			}

			for (int i = 0; i < bullet2Num; i++)
			{
				float hitRange =
					bullet2.GetSize().y / 2.0 *
					bullet2.scale.y;
				if (IsHit(
					bullet2Position[i],
					player.position,
					hitRange
				) && !cooldown)
				{
					life--;
					bar2.scale.x -= 0.254 / 8;
					cooldown = true;
				}
			}

			for (int i = 0; i < bullet3Num; i++)
			{
				float hitRange =
					bullet3.GetSize().y / 2.0 *
					bullet3.scale.y;
				if (IsHit(
					bullet3Position[i],
					player.position,
					hitRange) &&
					!cooldown)
				{
					life--;
					bar2.scale.x -= 0.254 / 8;
					cooldown = true;
				}
			}

			for (int i = 0; i < bullet5Num; i++)
			{
				float hitRange =
					bullet5.GetSize().y / 3 *
					bullet5.scale.y;
				if (IsHit(
					bullet5Position[i],
					player.position,
					hitRange) &&
					!cooldown)
				{
					life--;
					bar2.scale.x -= 0.254 / 8;
					cooldown = true;
				}
			}

			for (int i = 0; i < misairuNum; i++)
			{
				float hitRange =
					misairu.GetSize().y / 3 *
					misairu.scale.y;
				if (IsHit(
					misairuPosition[i],
					player.position,
					hitRange) &&
					!cooldown)
				{
					life--;
					bar2.scale.x -= 0.254 / 8;
					cooldown = true;
				}
			}

			if (cooldown)
			{
				time++;
				if (time >= 60)
				{
					time = 0;
					cooldown = false;
				}
			}

			if (life <= 0)
			{
				bar2.scale.x = 0;
				playerFlag = true;
				aiconFlag = true;
				bar2Flag = true;
				bar4Flag = true;
				bar5Flag = true;
				bar6Flag = true;
				bulletFlag = true;
				bullet2Flag = true;
				bullet3Flag = true;
				bullet4Flag = true;
				bullet5Flag = true;
				misairuFlag = true;
				if (bossFlag2 == false &&
					!bossFlag)
				{
					if (bossPosition[0].y < App::GetWindowSize().y / 2 - 115)
					{
						bossPosition[0] += Float3(
							0.0,
							0.0,
							0.0
						);
					}
					boss.position = bossPosition[0];
					boss.Draw();
				}
				count++;
				if (count > 60 &&
					bossFlag == false)
				{
					bossPosition[0] += Float3(
						0.0,
						-bossSpeed * 10,
						0.0
					);
				}
				if (bossPosition[0].y < -App::GetWindowSize().y + 800)
				{
					gameover.Draw();
					count2++;
					if (count2 > 180)
					{
						command = true;
						BGMSound.Stop();
						mode = Title;
					}
				}

			}

			for (int i = 0; i < bullet3Num; i++)
			{
				float hitRange =
					bullet2.GetSize().y / 2.0 *
					bullet2.scale.y;
				if (IsHit(
					bullet2Position[i],
					player.position,
					hitRange))
				{
					bullet2Position[i] =
						camera.position +
						-10000000000000;
				}
			}

			for (int i = 0; i < bullet3Num; i++)
			{
				float hitRange2 =
					bullet3.GetSize().y / 2.0 *
					bullet3.scale.y;
				if (IsHit(
					bullet3Position[i],
					player.position,
					hitRange2))
				{
					bullet3Position[i] =
						camera.position +
						-10000000000000;
				}
			}

			for (int i = 0; i < bullet5Num; i++)
			{
				float hitRange2 =
					bullet5.GetSize().y / 3 *
					bullet5.scale.y;
				if (IsHit(
					bullet5Position[i],
					player.position,
					hitRange2))
				{
					bullet5Position[i] =
						camera.position +
						-10000000000000;
				}
			}

			for (int i = 0; i < misairuNum; i++)
			{
				float hitRange2 =
					misairu.GetSize().y / 3 *
					misairu.scale.y;
				if (IsHit(
					misairuPosition[i],
					player.position,
					hitRange2))
				{
					misairuPosition[i] =
						camera.position +
						-10000000000000;
				}
			}

			if (bosspoint >= 25)
			{

				if (bossPosition[0].y < App::GetWindowSize().y / 2 - 115)
				{
					boss.position.y = 400;

					for (int i = 0; i < bossNum; i++)
					{
						float hitRange =
							boss.GetSize().x * 0.19;
						for (int j = 0; j < bulletNum; j++)
						{
							if (IsHit(
								bossPosition[0],
								bulletPosition[j],
								hitRange
							))
							{
								bulletPosition[j] = 1000;
							}
						}

						float hitRange2 =
							boss.GetSize().x * 0.19;
						for (int j = 0; j < bullet4Num; j++)
						{
							if (IsHit(
								bossPosition[0],
								bullet4Position[j],
								hitRange2
							))
							{
								bullet4Position[j] = 1000;
							}
						}

						bullet5Interval++;
						bullet5count++;
						if (bullet5Interval > 10)
						{
							bullet5Interval = 0;
							bullet5Position[bullet5Index] = Float3(
								boss.position.x + 40 * (bullet5count % 2 * 2 - 1), boss.position.y - 260, 0.0
							);
							bullet5Radian[bullet5Index] =
								0.0;

							bullet5Index++;
							if (bullet5Index >= bullet5Num)
								bullet5Index = 0;
						}

						misairuInterval++;
						misairucount++;
						if (misairuInterval > 100)
						{
							misairuInterval = 0;
							misairuPosition[misairuIndex] = Float3(
								boss.position.x - 135 * (misairucount % 2 * 2 - 1), boss.position.y - 180, 0.0
							);
							misairuRadian[misairuIndex] =
								0.0;

							misairuIndex++;
							if (misairuIndex >= misairuNum)
								misairuIndex = 0;
						}
					}
				}
				else
				{
					bossPosition[0] += Float3(
						0.0,
						-bossSpeed * 3,
						0.0
					);
				}
				boss.position = bossPosition[0];

				if (bossFlag == false)
				{
					boss.Draw();
				}
				for (int i = 0; i < bullet5Num; i++)
				{
					float hitRange =
						bullet5.GetSize().y * 1 / 2 *
						bullet5.scale.y;
					for (int j = 0; j < bulletNum; j++)
					{
						if (IsHit(
							bullet5Position[i],
							bulletPosition[j],
							hitRange
						))
						{
							bullet5Position[i] =
								camera.position +
								-10000000000000;
						}
					}

					float hitRange2 =
						bullet5.GetSize().y * 1.25*
						bullet5.scale.y;
					for (int j = 0; j < bullet4Num; j++)
					{
						if (IsHit(
							bullet5Position[i],
							bullet4Position[j],
							hitRange2
						))
						{
							bullet5Position[i] =
								camera.position +
								-10000000000000;
						}
					}
				}

				for (int i = 0; i < misairuNum; i++)
				{
					float hitRange =
						misairu.GetSize().y * 1 / 2 *
						misairu.scale.y;
					for (int j = 0; j < bulletNum; j++)
					{
						if (IsHit(
							misairuPosition[i],
							bulletPosition[j],
							hitRange
						))
						{
							bulletPosition[j] =
								camera.position +
								-10000000000000;
						}
					}

					float hitRange2 =
						misairu.GetSize().y * 0.65 *
						misairu.scale.y;
					for (int j = 0; j < bullet4Num; j++)
					{
						if (IsHit(
							misairuPosition[i],
							bullet4Position[j],
							hitRange2
						))
						{
							misairuPosition[i] =
								camera.position +
								-10000000000000;
						}
					}
				}
			}

			for (int i = 0; i < bullet4Num; i++)
			{
				bullet4Position[i] += Float3(
					sinf(bullet2Radian[i]),
					cosf(bullet2Radian[i]),
					0) * bulletSpeed;
				bullet4.position = bullet4Position[i];
				if (bullet4Flag == false)
				{
					bullet4.Draw();
				}
			}

			if (bar2Flag == false)
			{
				bar2.Draw();
			}
			if (bar4Flag == false)
			{
				bar4.Draw();
			}
			if (aiconFlag == false)
			{
				aicon.Draw();
			}

			if (bossPosition[0].y < App::GetWindowSize().y / 2 - 115)
			{
				float hitRange =
					boss.GetSize().x * 0.2f;
				for (int j = 0; j < bulletNum; j++)
				{
					if (IsHit(
						bossPosition[0],
						bulletPosition[j],
						hitRange
					) && bosscooldown == false)
					{
						bosslife--;
						bar6.scale.x -= 1.7f / 100;
						bosscooldown = true;
					}
				}

				float hitRange2 =
					boss.GetSize().x * 0.2;
				for (int j = 0; j < bullet4Num; j++)
				{
					if (IsHit(
						bossPosition[0],
						bullet4Position[j],
						hitRange2
					) && bosscooldown == false)
					{
						bosslife -= 10;
						bar6.scale.x -= 17.0f / 100;
						bosscooldown = true;
					}
				}

				if (bosscooldown)
				{
					bosstime++;
					if (bosstime >= 10)
					{
						bosstime = 0;
						bosscooldown = false;
					}
				}

				if (bosslife <= 0)
				{
					bar6.scale.x = 0;
					life = 8;
					if (bakuhathu3Flag == false)
					{
						bakuhathu3.position = Float3(
							-200, 360, 0
						);
						bakuhathu3.Draw();
						bakuhathu3count++;
						if (bakuhathu3count > 45)
						{
							bakuhathu3Flag = true;
						}
					}
					if (bakuhathu4Flag == false &&
						bakuhathu3Flag == true)
					{
						bakuhathu4.position = Float3(
							200, 440, 0
						);
						bakuhathu4.Draw();
						bakuhathu4count++;
						if (bakuhathu4count > 45)
						{
							bakuhathu4Flag = true;
						}
					}
					if (bakuhathu5Flag == false &&
						bakuhathu3Flag == true &&
						bakuhathu4Flag == true)
					{
						bakuhathu5.position = Float3(
							0, 400, 0
						);
						bakuhathu5.Draw();
						bakuhathu5count++;
						if (bakuhathu5count > 45)
						{
							bakuhathu5Flag = true;
							mode = Dragon;
						}
					}
					/*BGMSound.Stop();*/
				}

				if (bar6Flag == false)
				{
					bar6.Draw();
				}
				if (bar5Flag == false)
				{
					bar5.Draw();
				}
			}
			break;

		case Dragon:

			background.Draw();
			player.Draw();

			bosscount++;
			if (bosscount > 120)
			{
				gameclear.Draw();
				if (bosscount > 240)
				{
					command = true;
					BGMSound.Stop();
					mode = Title;
				}
			}
			break;
		}
	}
	return 0;
}