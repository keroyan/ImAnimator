#include <unordered_map>
#include "imgui.h"
#include "imgui_internal.h"

template <typename T>
class Animator {
public:
    Animator(T a, T b, bool* when, float speed = 2.f) noexcept
    {
        this->startPoint = a; // the point A
        this->endPoint = b; // the point B
        this->bWhen = when; // when shall it go from A to B, if true it will go from A to B and if it's false then from B to A
        this->flAnimationSpeed = speed; // the speed this animation shall happen
    }

    auto GetCurrentAnimation(ImGuiID id) noexcept
    {
        auto itAnimation = mAnimator.find(id);
        if (itAnimation == mAnimator.end())
        {
            mAnimator.insert({ id, 0.f });
            itAnimation = mAnimator.find(id);
        }

        return itAnimation;
    }

    T Update(ImGuiID id) noexcept
    {
        auto itAnimation = GetCurrentAnimation(id);
        itAnimation->second = Clamp(itAnimation->second + ImGui::GetIO().DeltaTime * flAnimationSpeed * (*bWhen ? 1.f : -1.f), 0.f, 1.0f);
        return Lerp(startPoint, endPoint, itAnimation->second);
    }

private:
    template<typename T> static inline T Clamp(T v, T mn, T mx) { return (v < mn) ? mn : (v > mx) ? mx : v; }
    template<typename T> static inline T Lerp(T a, T b, float t) { return (T)(a + (b - a) * t); }
    static inline ImVec2 Lerp(const ImVec2& a, const ImVec2& b, float t) { return ImVec2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t); }
    static inline ImVec2 Lerp(const ImVec2& a, const ImVec2& b, const ImVec2& t) { return ImVec2(a.x + (b.x - a.x) * t.x, a.y + (b.y - a.y) * t.y); }
    static inline ImVec4 Lerp(const ImVec4& a, const ImVec4& b, float t) { return ImVec4(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t); }
    static inline ImColor Lerp(const ImColor& a, const ImColor& b, float t) { return ImColor(a.Value.x + (b.Value.x - a.Value.x) * t, a.Value.y + (b.Value.y - a.Value.y) * t, a.Value.z + (b.Value.z - a.Value.z) * t, a.Value.w + (b.Value.w - a.Value.w) * t); }

    std::unordered_map<ImGuiID, float> mAnimator;
    T startPoint, endPoint;
    float flAnimationSpeed;
    bool* bWhen;
};
