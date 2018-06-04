#include "Scene.h"

Scene::Scene(int Priority)
{
	for( int i=0 ; i<10 ; i++ )
	{
		if(m_Scene[i]==NULL)
		{
			m_Scene[i]=this;
			break;
		}
	}
}


void Scene::UpdateAll()
{

		for(int i=0 ; i<10 ;i++)
		{
			if(m_Scene[i]!=NULL)
			{
				m_Scene[i]->Update();
			}
		
		}
}
void Scene::DrawAll()
{

		for(int i=0 ; i<10 ;i++)
		{
			if(m_Scene[i]!=NULL)
			{
				m_Scene[i]->Draw();
			}
		
		}
	
}

void Scene::Relese()
{

	for(int i=0 ; i<10 ;i++)
	{
	
		if(m_Scene[i]!=NULL)
		{
			m_Scene[i]=NULL;
			Uninit();
			delete this;
			break;
		}
	
	}

}

void Scene::ReleaseAll()
{
	for(int i=0 ; i<10 ; i++)
	{
		if(m_Scene[i]!=NULL)
		{
			m_Scene[i]->Relese();
		}
	}
}