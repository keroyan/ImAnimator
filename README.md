# ImAnimator
A simple header-only animator class to help you make any imgui element dynamic and beautiful

# Usage

This animator is for mulitple controls, and is not suitable for a single usage case.

In this case we go from 0 -> 15 if V is true, if it is false it will go back to 0! Basic stuff!
```cpp
    static Animator<float> enabledAnimator(0.f, 15.f, 4.f);
    float enabledValue = enabledAnimator.Update(id, v);
```

In a case where you want to animate colors, you can do that!
```cpp
    static Animator<ImColor> colorAnimator(ImColor(255, 21, 26, 255), ImColor(21, 26, 54, 255), 4.f);
    ImColor colorAnimation = colorAnimator.Update(id, v);
```

Remember that you need to have controls with ids because that's how the animator knows each controls individually!

# Real World Usage

This control is an basic checkbox with a nice animation attached to it, which makes the thickness larger when the checkbox gets enabled,
the purpose of me showing you this is for you to understand how it would work in a real world scenario!
```cpp
bool Checkbox(const char* name, bool* v)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    const ImGuiID id = window->GetID(name);
    const ImRect bb = ImRect(window->DC.CursorPos, window->DC.CursorPos + ImVec2(20, 20));

    ImGui::ItemSize(bb);
    if (!ImGui::ItemAdd(bb, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);

    if (pressed)
        *v = !(*v);

    static Animator<float> enabledAnimator(0.f, 13.f, 4.f);
    float enabledValue = enabledAnimator.Update(id, v);

    window->DrawList->AddRect(bb.Min, bb.Max, ImColor(255, 255, 255, 255), 0.f);
    window->DrawList->AddRect(bb.Min + ImVec2(enabledValue, enabledValue), bb.Max - ImVec2(enabledValue, enabledValue), ImColor(255, 255, 255, 255), 0.f, 0, enabledValue);

    return true;
}
```
