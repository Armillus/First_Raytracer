/*
 * Created on Wed Apr 29 2020
 *
 * Copyright (c) raytracer 2020 Arthur Lang
 * Unittest_Viewer.cpp
 */

#include <gtest/gtest.h>

#include "Viewer.hpp"
#include "Vector3.hpp"
#include "Resolution.hpp"
#include "Camera.hpp"
#include "RayTracer.hpp"
#include "Core.hpp"

TEST(Viewer, moveCamera)
{
    const char **av = new const char*[3];
    av[0] = "./unit_tests";
    av[1] = "assets/yeet.json";
    av[2] = nullptr;
    rt::Resolution res = { 1920, 1080 };
    rt::Viewer v(res, 2, av);

    rt::maths::Vector3f pos(0, 0, 0);
    v.moveCamToLeft();
    v.moveCamToRight();
    v.moveCamToRight();
    v.moveCamUp();
    v.moveCamDown();
    v.moveCameraBackward();
    v.moveCameraForward();
    v.moveCameraForward();
    v.moveCameraForward();
    rt::Camera cam = v.camera();
    ASSERT_FLOAT_EQ(pos.x + 1, cam.origin().x);
    ASSERT_FLOAT_EQ(pos.y, cam.origin().y);
    ASSERT_FLOAT_EQ(pos.z + 8, cam.origin().z);

    delete[] av;
}

TEST(Viewer, rotateCamera)
{
    const char **av = new const char*[3];
    av[0] = "./unit_tests";
    av[1] = "assets/yeet.json";
    av[2] = nullptr;
    rt::Resolution res = { 1920, 1080 };
    rt::Viewer v(res, 2, av);

    rt::maths::Vector3f test(0, 0, 0);
    v.rotateCamDown();
    v.rotateCamDown();
    v.rotateCamUp();
    v.rotateCamToLeft();
    v.rotateCamToRight();
    rt::Camera cam = v.camera();
    ASSERT_FLOAT_EQ(test.x, cam.direction().x);
    ASSERT_FLOAT_EQ(test.y - 1, cam.direction().y);
    ASSERT_FLOAT_EQ(test.z - 1, cam.direction().z);

    delete[] av;
}

TEST(Viewer, withScene)
{
    const char **av = new const char*[3];
    av[0] = "./unit_tests";
    av[1] = "assets/yeet.json";
    av[2] = nullptr;
    rt::Resolution res = { 1920, 1080 };
    rt::Camera camera(0, 0, 10, res.width, res.height);
    rt::Scene scene;
    rt::Viewer v(scene, camera, 2, av);

    rt::maths::Vector3f test(0, 0, 0);
    v.rotateCamDown();
    v.rotateCamDown();
    v.rotateCamUp();
    v.rotateCamToLeft();
    v.rotateCamToRight();
    rt::Camera cam = v.camera();
    ASSERT_FLOAT_EQ(test.x, cam.direction().x);
    ASSERT_FLOAT_EQ(test.y - 1, cam.direction().y);
    ASSERT_FLOAT_EQ(test.z - 1, cam.direction().z);

    delete[] av;
}

TEST(Viewer, show)
{
    const char **av = new const char*[3];
    av[0] = "./unit_tests";
    av[1] = "assets/empty.json";
    av[2] = nullptr;
    rt::Resolution res = { 1920, 1080 };
    rt::Camera camera(0, 0, 10, res.width, res.height);
    rt::Scene scene;
    rt::Viewer v(scene, camera, 2, av);
    std::unique_ptr<rt::Renderer> renderer = std::make_unique<rt::RayTracer>(rt::DEFAULT_WIN_RES);
    std::unique_ptr<rt::IGraphicalLibrary> graphicLibrary = std::make_unique<rt::SfmlLibrary>(rt::DEFAULT_WIN_RES, rt::DEFAULT_WIN_TITLE);

    v.show(graphicLibrary, renderer);
    v.changeScreenResolution(rt::Resolution {200, 200});
    delete[] av;
}