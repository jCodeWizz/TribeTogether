#include "ClientLayer.h"
#include "ServerPacket.h"

#include "Walnut/Input/Input.h"
#include "Walnut/ImGui/ImGuiTheme.h"
#include "Walnut/Serialization/BufferStream.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "misc/cpp/imgui_stdlib.h"


namespace TT {

	static Walnut::Buffer s_ScratchBuffer;

	static void DrawRect(glm::vec2 pos, glm::vec2 size, uint32_t colour) {
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		ImVec2 min = ImGui::GetWindowPos() + ImVec2(pos.x, pos.y);
		ImVec2 max = min + ImVec2(size.x, size.y);
		drawList->AddRectFilled(min, max, colour);
	}

	void ClientLayer::OnAttach() {
		s_ScratchBuffer.Allocate(10 * 1024 * 1024);

		m_Client.SetDataReceivedCallback([this](const Walnut::Buffer buffer) { OnDataReceived(buffer); });
	}

	void ClientLayer::OnDetach() {
	}

	void ClientLayer::OnUpdate(float dt) {
		if (m_Client.GetConnectionStatus() != Walnut::Client::ConnectionStatus::Connected) {
			return;
		}

		glm::vec2 dir{ 0.0f, 0.0f };

		if (Walnut::Input::IsKeyDown(Walnut::KeyCode::W)) {
			dir.y = -1;
		}
		else if (Walnut::Input::IsKeyDown(Walnut::KeyCode::S)) {
			dir.y = 1;
		}

		if (Walnut::Input::IsKeyDown(Walnut::KeyCode::A)) {
			dir.x = -1;
		}
		else if (Walnut::Input::IsKeyDown(Walnut::KeyCode::D)) {
			dir.x = 1;
		}

		if (glm::length(dir) > 0.0f) {
			dir = glm::normalize(dir);
			const float speed = 150.0f;
			m_PlayerVelocity = dir * speed;
		}

		m_PlayerPosition += m_PlayerVelocity * dt;
		m_PlayerVelocity = glm::mix(m_PlayerVelocity, glm::vec2(0.0f), 10.0f * dt);

		Walnut::BufferStreamWriter stream(s_ScratchBuffer);

		stream.WriteRaw(PacketType::ClientUpdate);
		stream.WriteRaw<glm::vec2>(m_PlayerPosition);
		stream.WriteRaw<glm::vec2>(m_PlayerVelocity);
		m_Client.SendBuffer(stream.GetBuffer());
	}

	void ClientLayer::OnUIRender() {
		Walnut::Client::ConnectionStatus status = m_Client.GetConnectionStatus();

		if (status == Walnut::Client::ConnectionStatus::Connected) {
			DrawRect(m_PlayerPosition, { 50.0f, 50.0f }, 0xffffffff);

			m_PlayerDataMutex.lock();
			std::map<uint32_t, PlayerData> playerData = m_PlayerData;
			m_PlayerDataMutex.unlock();

			for (const auto& [id, data] : playerData) {
				if (id == m_PlayerID) continue;

				DrawRect(data.Position, { 50.0f, 50.0f }, 0xff00ffff);
			}

		} else {
			bool readOnly = status != Walnut::Client::ConnectionStatus::Disconnected;
			ImGui::Begin("Connect to server");

			if (status == Walnut::Client::ConnectionStatus::FailedToConnect) {
				ImGui::TextColored(ImColor(Walnut::UI::Colors::Theme::error), "Failed to connect.");
			} else if (status == Walnut::Client::ConnectionStatus::Connecting) {
				ImGui::TextColored(ImColor(Walnut::UI::Colors::Theme::textDarker), "Connecting. . .");
			}
			ImGui::InputText("Server Address", &m_ServerAddress);
			if (ImGui::Button("Connect")) {
				m_Client.ConnectToServer(m_ServerAddress);
			}

			ImGui::End();
		}

	}

	void ClientLayer::OnDataReceived(const Walnut::Buffer buffer) {
		Walnut::BufferStreamReader stream(buffer);
		PacketType type;
		stream.ReadRaw(type);

		switch (type) {
		case PacketType::ClientConnect:
			stream.ReadRaw<uint32_t>(m_PlayerID);
			break;
		case PacketType::ClientUpdate:


			m_PlayerDataMutex.lock();
			stream.ReadMap(m_PlayerData);
			m_PlayerDataMutex.unlock();
			break;
		}
		
	}
}