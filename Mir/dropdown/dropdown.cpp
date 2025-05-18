#include <algorithm> 
#include <unordered_map>
#include "dropdown.h"

static void performSearch(const std::string& searchStr, std::vector<size_t>& matchingIds, const std::vector<std::string>& options) {
    matchingIds.clear();
    std::string lowerSearchStr = searchStr;
    std::transform(lowerSearchStr.begin(), lowerSearchStr.end(), lowerSearchStr.begin(), 
                  [](unsigned char c){ return std::tolower(c); });
    
    for (size_t i = 0; i < options.size(); i++) {
        if(options[i].contains(lowerSearchStr)){
            matchingIds.push_back(i);
        }
    }
}

static int TextEditCallback(ImGuiInputTextCallbackData* data) {
    if (data->EventFlag == ImGuiInputTextFlags_CallbackEdit) {
        auto* userData = static_cast<std::pair<std::vector<size_t>*, const std::vector<std::string>*>*>(data->UserData);
        std::string currentText(data->Buf);
        performSearch(currentText, *userData->first, *userData->second);
    }
    return 0;
}
struct DropdownState {
    std::vector<size_t> matchingIds;
    bool focused = false;
    bool wasOpen = false;
    std::pair<std::vector<size_t>*, const std::vector<std::string>*> callbackData;
    
    DropdownState() : callbackData(&matchingIds, nullptr) {}
};
namespace Mir{

        void Dropdown(std::string& _str, const std::string& _id, const std::vector<std::string>& _options) {
            static std::unordered_map<std::string, DropdownState> states;
            DropdownState& state = states[_id];
            state.callbackData.second = &_options;

            bool isOpen = ImGui::BeginCombo(("##"+_id).c_str(), _str.c_str());
            
            // Check if the combo was open but now is closed (clicked outside of the popup)
            if (state.wasOpen && !isOpen) {
                state.focused = false;
            }
            
            state.wasOpen = isOpen;
        
            
            if (isOpen) {
                if (!state.focused) { 
                    ImGui::SetKeyboardFocusHere(); 
                    state.focused = true;
                }
        
                // callbackdata for comparing textinputs m_str contents to vector<std::string> options 
                // and also updating matchingids which is used later to draw only the indexes with match
                if (ImGui::InputText("##search", &_str,
                    ImGuiInputTextFlags_EnterReturnsTrue | 
                    ImGuiInputTextFlags_AutoSelectAll | 
                    ImGuiInputTextFlags_CallbackEdit,
                    TextEditCallback,
                    &state.callbackData)) {
                state.focused = false;
                ImGui::CloseCurrentPopup();
                }
        
                ImGui::Separator();
        
                
                // rendering "recommendations" from the edit callback 
                for (size_t idx = 0; idx < state.matchingIds.size(); idx++) {
                    size_t i = state.matchingIds[idx];
                    bool is_selected = false;
                    if (ImGui::Selectable(_options[i].c_str(), is_selected)) {
                        _str = _options[i];
                        state.focused = false;
                        ImGui::CloseCurrentPopup();
                    }
                    
                    if (ImGui::IsItemFocused() && 
                    (ImGui::IsKeyPressed(ImGuiKey_Enter))) {
                        _str = _options[i];
                        state.focused = false;
                        ImGui::CloseCurrentPopup();
                    }
                }
                ImGui::EndCombo(); 
            };
        }

} // namespace Mir

