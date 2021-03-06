#pragma once
#include "ObjectSet.h"
#include "ObjModel.h"
#include "StageData.h"
#include "RotatingCube.h"
#include "TaskList.h"
#include "Clock.h"
#include "AnswerBoard.h"
#include "Button.h"
#include "MainBackground.h"

namespace Game
{
	namespace GamePlay
	{
		class GameMain : public Engine::ObjectSet<Engine::GameObject>
		{
		private:
			RotatingCube* rotCube_ = nullptr;
			AnswerBoard* ansBoard_ = nullptr;
			Engine::TaskList tasks_;

			Engine::Button &back_;

			Clock& clk_;
			float timer_ = -1;

			static Mix_Music* bgm_;
		public:
			static void ClearMusic();
			GameMain(const decltype(*Stages)& stage,MainBackground* bk = nullptr);

			void Update(float d);

			void Exit();
		};
	}
}