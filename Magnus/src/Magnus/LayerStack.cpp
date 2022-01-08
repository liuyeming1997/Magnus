#include "mgpch.h"
#include "LayerStack.h"

namespace Magnus {
	LayerStack::LayerStack() {
		
	}
	LayerStack::~LayerStack() {
		
		m_Layers.clear();
	}
	void LayerStack::PushLayer(Layer* layer) {
		layer->OnAttach();
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::move(layer));
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		overlay->OnAttach();
		m_Layers.emplace_back(std::move(overlay));
		
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsertIndex--;
			layer->OnDetach();
		}
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			overlay->OnDetach();
		}
			
	}
}