﻿#include "Scene_1.h"



Scene_1::Scene_1()
{
	LoadResources();
}


Scene_1::~Scene_1()
{
	SAFE_DELETE(TileMap);
	SAFE_DELETE(board);
	SAFE_DELETE(gridGame);

}

void Scene_1::KeyState(BYTE * state)
{

	if (simon->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}


	if (simon->GetIsDeadth() || isWaitResetGame || isGameOver)
	{
		return;
	}


	if (simon->GetIsAutoGoX() == true) // đang chế độ tự đi thì ko xét phím
		return;


	//simon->Jump();

	//return;

	if (simon->isJumping && simon->isWalking)
		return;

	if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		simon->Sit();

		if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
			simon->Right();

		if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
			simon->Left();

		return;
	}
	else
		simon->Stop();

	if (simon->isJumping)
		return;


	if (simon->isAttacking) // đang attack
	{
		float vx, vy;
		simon->GetSpeed(vx, vy);
		simon->SetSpeed(0, vy); 

		return;
	}

	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		//if (simon->isAttacking) // đang attack
		//{
		//	float vx, vy;
		//	simon->GetSpeed(vx, vy);
		//	simon->SetSpeed(0, vy);
		//	DebugOut(L"DIK_RIGHT & attack \n");

		//	return;
		//} 

		simon->Right();
		simon->Go();
	}
	else
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			//if (simon->isAttacking) // đang attack
			//{
			//	float vx, vy;
			//	simon->GetSpeed(vx, vy);
			//	simon->SetSpeed(0, vy);
			//	DebugOut(L"DIK_LEFT & attack \n");

			//	return;
			//}

			simon->Left();
			simon->Go(); 

		}
		else
		{ 

			//if (simon->isAttacking) // đang attack
			//{
			//	float vx, vy;
			//	simon->GetSpeed(vx, vy);
			//	simon->SetSpeed(0, vy);
			//	DebugOut(L"DIK_RIGHT & attack \n");

			//	return;
			//}

			simon->Stop();
		}


}

void Scene_1::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_R) // render bbox
	{
		if (isDebug_RenderBBox == 0)
			isDebug_RenderBBox = 1;
		else
			isDebug_RenderBBox = 0;
	}

	if (simon->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}

	if (isGameOver)
	{
		switch (KeyCode)
		{
		case DIK_UP:
		{
			GameOverSelect = GAMEOVER_SELECT_CONTINUE;
			break;
		}
		case DIK_DOWN:
		{
			GameOverSelect = GAMEOVER_SELECT_END;
			break;
		}
		case DIK_RETURN:
		{
			if (GameOverSelect == GAMEOVER_SELECT_CONTINUE)
			{
				SceneManager::GetInstance()->SetScene(new Scene_1());
			}
			else
				if (GameOverSelect == GAMEOVER_SELECT_END)
				{
					DestroyWindow(Game::GetInstance()->GetWindowHandle()); // thoát
				}
			break;
		}
		}


		return;
	}


	if (simon->GetIsDeadth() || isWaitResetGame)
	{
		return;
	}


	//	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	if (KeyCode == DIK_ESCAPE)
		DestroyWindow(/*hWnd*/ Game::GetInstance()->GetWindowHandle()); // thoát

	if (KeyCode == DIK_Q)
		simon->SetPosition(SIMON_POSITION_DEFAULT);



	if (KeyCode == DIK_1) // vị trí simon
	{
		DebugOut(L"[SIMON] X = %f , Y = %f \n", simon->GetX() + 10, simon->GetY());
	}




	if (KeyCode == DIK_2) // lấy tọa độ world của chuột 
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(Game::GetInstance()->GetWindowHandle(), &p);
		DebugOut(L"[MOUSE POSITION] x: %d , y = %d\n", p.x + (int)camera->GetXCam(), p.y + (int)camera->GetYCam());

	}


	if (KeyCode == DIK_3) // set vi tri simon 1275 
	{
		DebugOut(L"[SET POSITION SIMON] x = 1275 \n");
		simon->SetPosition(1275.0f, 0);
	}
	 

	if (simon->GetIsAutoGoX() == true) // đang chế độ tự đi thì ko xét phím
		return;



	if (KeyCode == DIK_X && simon->isProcessingOnStair == 0) // không phải đang xử lí việc đi trên thang thì đc đánh
	{
		simon->Attack(eType::MORNINGSTAR);
	}

	if (KeyCode == DIK_Z && simon->isProcessingOnStair == 0)
	{
		simon->Attack(simon->GetTypeWeaponCollect()); // attack với vũ khí phụ đang nhặt
	}

	if (simon->isJumping && simon->isWalking)
	{
		return;
	}





	if (KeyCode == DIK_SPACE && simon->isOnStair == false)
	{
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT) || Game::GetInstance()->IsKeyDown(DIK_RIGHT))
		{
			simon->Stop();
			simon->SetSpeed(SIMON_WALKING_SPEED * simon->GetDirection(), -SIMON_VJUMP);
			simon->isJumping = 1;
			simon->isWalking = 1;
		}
		else
		{
			simon->Jump();
		}
	}

}

void Scene_1::OnKeyUp(int KeyCode)
{
	if (simon->GetFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}

	if (simon->GetIsDeadth() || isWaitResetGame)
	{
		return;
	}

	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	switch (KeyCode)
	{
	case DIK_SPACE:
		//simon->Sit();
		break;
	}
}


void Scene_1::LoadResources()
{
	TextureManager * _textureManager = TextureManager::GetInstance(); // Đã gọi load resource
	
 
	sound = Sound::GetInstance();

	
	TileMap = new Map();
	TileMap->LoadMap(eType::MAP1);

	
	camera = SceneManager::GetInstance()->GetCamera();
	camera->SetAllowFollowSimon(true);

	camera->SetBoundary(0.0f, (float)(TileMap->GetMapWidth() - camera->GetWidth())); // set biên camera dựa vào kích thước map
	camera->SetBoundaryBackup(camera->GetBoundaryLeft(), camera->GetBoundaryRight()); // backup lại biên

	camera->SetPosition(0, 0);


	simon = new Simon(camera);

	board = new Board(BOARD_DEFAULT_POSITION_X, BOARD_DEFAULT_POSITION_Y);

	simon->SetPosition(SIMON_POSITION_DEFAULT);
	simon->SetPositionBackup(SIMON_POSITION_DEFAULT);


	_gameTime = new GameTime();

	_spriteLagerHeart = new GSprite(TextureManager::GetInstance()->GetTexture(eType::LARGEHEART), 100);


	ResetResource();
}


void Scene_1::ResetResource()
{
	SAFE_DELETE(gridGame);
	gridGame = new Grid();
	gridGame->ReadFileToGrid("Resources/map/Obj_1.txt"); // đọc lại các object từ list

	listItem.clear();
	listEffect.clear();

	_gameTime->SetTime(0); // đếm lại từ 0

	sound->StopAll();


	sound->Play(eSound::musicState1, true); // mở lại nhạc nền

											/* Set Chờ hiển thị màn đen */
	isWaitResetGame = true;
	TimeWaitedResetGame = 0;

	/*init gameover*/
	isGameOver = false;
	GameOverSelect = GAMEOVER_SELECT_CONTINUE;
}


void Scene_1::Update(DWORD dt)
{
	if (isGameOver)
		return;

#pragma region xử lí vẽ màn đen trước khi bắt đầu game
	if (isWaitResetGame)
	{
		TimeWaitedResetGame += dt;
		if (TimeWaitedResetGame >= TIME_LIMIT_WAIT_RESET_GAME)
		{
			isWaitResetGame = false;

		}
		else
			return;
	}
#pragma endregion


	if (simon->GetFreeze() == true)
	{
		simon->UpdateFreeze(dt);
		if (simon->GetFreeze() == true)
			return;
	}


	if (_gameTime->GetTime() >= GAME_TIME_SCENE1) // hết thời gian
	{
		if (simon->GetIsDeadth())
		{
			simon->TimeWaitedAfterDeath += dt;
			if (simon->TimeWaitedAfterDeath >= 1500)
			{
				if (simon->GetLives() == 0)
				{
					isGameOver = true;
				}
				else
				{
					bool result = simon->LoseLife(); // đã khôi phục x,y 
					camera->RestorePosition(); // khôi phục vị trí camera;
					camera->RestoreBoundary(); // khôi phục biên camera

					if (result == true) // còn mạng để chơi tiếp, giảm mạng reset máu xong
					{
						ResetResource(); // reset lại game
					}
				}
				return;
			}
		}
		else // chưa chết mà hết máu hoặc time thì set trạng thái isDeadth
		{
			simon->SetDeadth();
		}
	}
	else
		_gameTime->Update(dt);


	if (GAME_TIME_SCENE1 - _gameTime->GetTime() <= 30) // đúng còn lại 30 giây thì bật sound loop
	{
		if (_gameTime->CheckIsJustChanged() == true) // Kiểm tra _time vừa thay đổi thì mới play nhạc. Nếu chỉ kt <=30s thì cứ mỗi deltatime nó sẽ Play nhạc -> thừa, ko đều
		{
			sound->Play(eSound::soundStopTimer);
		}
	}

	gridGame->GetListObject(listObj, camera);

	//DebugOut(L"[GRID] size = %d\n", listObj.size());

	simon->Update(dt, &listObj);

	if (camera->AllowFollowSimon())
	{
		camera->SetPosition(simon->GetX() - SCREEN_WIDTH / 2 + 30, camera->GetYCam()); // cho camera chạy theo simon
	}
	camera->Update(dt);

	for (UINT i = 0; i < listObj.size(); i++)
		listObj[i]->Update(dt, &listObj);  // đã kiểm tra "Alive" lúc lấy từ lưới ra

	for (UINT i = 0; i < listItem.size(); i++)
		if (listItem[i]->GetFinish() == false)
			listItem[i]->Update(dt, &listObj); // trong các hàm update chỉ kiểm tra va chạm với đất

	for (UINT i = 0; i < listEffect.size(); i++)
		if (listEffect[i]->GetFinish() == false)
			listEffect[i]->Update(dt);

	CheckCollision();
}


void Scene_1::Render()
{
	if (isWaitResetGame) // vẽ màn đen trước khi bắt đầu game
		return; // thoát và ko vẽ gì

	if (!isGameOver)
	{
		TileMap->DrawMap(camera);

		for (UINT i = 0; i < listObj.size(); i++)
			listObj[i]->Render(camera);

		for (UINT i = 0; i < listItem.size(); i++)
			if (listItem[i]->GetFinish() == false)
				listItem[i]->Render(camera);

		for (UINT i = 0; i < listEffect.size(); i++)
			if (listEffect[i]->GetFinish() == false)
				listEffect[i]->Render(camera);

		simon->Render(camera);
	}
	else
	{
		Text.Draw(200, 200, "GAME OVER");
		Text.Draw(215, 250, "CONTINUE");
		Text.Draw(215, 280, "END");
		switch (GameOverSelect)
		{
		case GAMEOVER_SELECT_CONTINUE:
		{
			_spriteLagerHeart->Draw(175, 245);
			break;
		}
		case GAMEOVER_SELECT_END:
		{
			_spriteLagerHeart->Draw(175, 275);
			break;
		}
		}
	}

	board->Render(simon, 1, GAME_TIME_SCENE1 - _gameTime->GetTime(), NULL);



}

void Scene_1::CheckCollision()
{
	CheckCollisionWeapon();

	CheckCollisionSimonWithItem();

	CheckCollisionSimonWithObjectHidden();
}

void Scene_1::CheckCollisionWeapon()
{
	for (auto& objWeapon : simon->mapWeapon)
	{
		if (objWeapon.second->GetFinish() == false) // Vũ khí đang hoạt động
		{
			for (UINT i = 0; i < listObj.size(); i++)
				if (listObj[i]->GetLastTimeAttacked() != objWeapon.second->GetLastTimeAttack()) // Nếu chưa xét va chạm của lượt attack này ở các frame trước
				{
					if (objWeapon.second->isCollision(listObj[i]) == true) // nếu có va chạm
					{
						bool RunEffectHit = false;
						GameObject *gameObj = listObj[i];
						switch (gameObj->GetType())
						{
		
						case eType::TORCH:
						{ 
							gameObj->SubHealth(1);
							listItem.push_back(GetNewItem(gameObj->GetId(), gameObj->GetType(), gameObj->GetX() + 5, gameObj->GetY()));// hiệu ứng hit
							RunEffectHit = true;
							break; 
						}
					 
						default:
							break;
						}

						if (RunEffectHit)
						{
							listEffect.push_back(new Hit(listObj[i]->GetX() + 10, listObj[i]->GetY() + 14)); // hiệu ứng hit
							listEffect.push_back(new Fire(gameObj->GetX() - 5, gameObj->GetY() + 8)); // hiệu ứng lửa

							sound->Play(eSound::soundHit);

							if (objWeapon.second->GetType() == eType::DAGGER)
							{
								objWeapon.second->SetFinish(true);
							}

						}
						gameObj->SetLastTimeAttacked(objWeapon.second->GetLastTimeAttack()); // bị đánh trúng->update thời gian bị đánh lần cuối
					}
				}
		}
	}
	 
}

void Scene_1::CheckCollisionSimonWithItem()
{
	for (UINT i = 0; i < listItem.size(); i++)
		if (listItem[i]->GetFinish() == false && listItem[i]->isWaitingDisplay() == false) // chưa kết thúc và "không phải" đang chờ để hiển thị
		{
			if (simon->isCollisionWithItem(listItem[i]) == true) // có va chạm
			{
				switch (listItem[i]->GetType())
				{

				case eType::LARGEHEART:
				{
					simon->SetHeartCollect(simon->GetHeartCollect() + 5);
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectItem);
					break;
				}

				case eType::UPGRADEMORNINGSTAR:
				{
					MorningStar * objMorningStar = dynamic_cast<MorningStar*>(simon->mapWeapon[eType::MORNINGSTAR]);
					objMorningStar->UpgradeLevel(); // Nâng cấp vũ khí roi

					listItem[i]->SetFinish(true);
					simon->SetFreeze(true); // bật trạng thái đóng băng
					sound->Play(eSound::soundCollectWeapon);
					break;
				}

				case eType::ITEMDAGGER:
				{
					simon->ProcessWeaponCollect(eType::DAGGER);
					listItem[i]->SetFinish(true);
					break;
				}

				case eType::BONUS:
				{
					listItem[i]->SetFinish(true);
					sound->Play(eSound::soundCollectItem);
					simon->SetScore(simon->GetScore() + 1000);
					listEffect.push_back(new EffectMoney(listItem[i]->GetX(), listItem[i]->GetY(), eType::EFFECT_MONEY_1000));

					break;
				}

				default:
					DebugOut(L"[CheckCollisionSimonWithItem] Khong nhan dang duoc loai Item!\n");
					break;
				}
			}
		}
}

void Scene_1::CheckCollisionSimonWithObjectHidden()
{
	for (UINT i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == eType::OBJECT_HIDDEN)
		{
			GameObject * gameObject = listObj[i];
			if (gameObject->GetHealth() > 0)
			{
				if (simon->isCollitionObjectWithObject(gameObject))
				{
					switch (gameObject->GetId())
					{
					case 7: // đụng trúng cửa
					{
						SceneManager::GetInstance()->SetScene(new Scene_2(simon, _gameTime));
						return;
						break;
					}

					case 8:
					{
						sound->Play(eSound::soundDisplayMonney);
						listItem.push_back(GetNewItem(gameObject->GetId(), gameObject->GetType(), simon->GetX(), simon->GetY()));
						break;
					}
					}
					gameObject->SubHealth(1);

				}
			}
		}
	}
}


Item * Scene_1::GetNewItem(int Id, eType Type, float X, float Y)
{
	if (Type == eType::TORCH)
	{
		if (Id == 1 || Id == 4)
			return new LargeHeart(X, Y);

		if (Id == 2 || Id == 3)
			return new UpgradeMorningStar(X, Y);

		if (Id == 5)
			return new ItemDagger(X, Y);
	}

	if (Type == eType::OBJECT_HIDDEN)
	{
		if (Id == 8)
			return new Bonus(1240, 305);

	}

	return new LargeHeart(X, Y);
}