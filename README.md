# ImAnimator
A simple lightweight animator class to help you make any imgui element dynamic and beautiful

# Usage

This animator is for mulitple controls, and is not suitable for a single usage case.

In this case we go from 0 -> 15 if V is true, if it is false it will go back to 0! Basic stuff!
```cpp
    static Animator<float> enabledAnimator(0.f, 15.f, v, 4.f);
    float enabledValue = enabledAnimator.Update(id);
```

In a case where you want to animate colors, you can do that!
```cpp
    static Animator<ImColor> colorAnimator(ImColor(255, 21, 26, 255), ImColor(21, 26, 54, 255), v, 4.f);
    ImColor colorAnimation = colorAnimator.Update(id);
```

Remember that you need to have controls with ids because that's how the animator knows each controls individually!
