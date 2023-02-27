// This file is part of the AliceVision project.
// Copyright (c) 2021 AliceVision contributors.
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
#pragma once

// SFMData
#include <aliceVision/sfmData/SfMData.hpp>
#include <aliceVision/image/Image.hpp>

#include <string>
#include <vector>
#include <array>

namespace aliceVision {
namespace photometricStereo {

void normalIntegration(const std::string& inputPath, const bool& perspective, const int& downscale, const std::string& outputFodler);

void normalIntegration(const sfmData::SfMData& sfmData, const std::string& inputPath, const bool& perspective, const int& downscale, const std::string& outputFodler);

void DCT_integration(const image::Image<image::RGBfColor>& normals, image::Image<float>& depth, bool perspective, const Eigen::Matrix3f& K, const image::Image<float>& normalsMask);

void normal2PQ(const image::Image<image::RGBfColor>& normals, Eigen::MatrixXf& p, Eigen::MatrixXf& q, bool perspective, const Eigen::Matrix3f& K, const image::Image<float>& normalsMask);

void getDivergenceField(const Eigen::MatrixXf& p, const Eigen::MatrixXf& q, Eigen::MatrixXf& f);

void setBoundaryConditions(const Eigen::MatrixXf& p, const Eigen::MatrixXf& q, Eigen::MatrixXf& f);

void adjustScale(const sfmData::SfMData& sfmData, image::Image<float>& initDepth, size_t viewID);

void getZ0FromLandmarks(const sfmData::SfMData& sfmData, image::Image<float>& z0, image::Image<float>& mask_z0, const size_t viewID, const image::Image<float>& mask);

void smoothIntegration(const image::Image<image::RGBfColor>& normals, image::Image<float>& depth, bool perspective, const Eigen::Matrix3f& K, const image::Image<float>& mask, const image::Image<float>& z0, const image::Image<float>& mask_z0);

void convertZtoDistance(const image::Image<float>& zMap, image::Image<float>& distanceMap, const Eigen::Matrix3f& K);

void convertDistanceToZ(const image::Image<float>& distanceMap, image::Image<float>& zMap, const Eigen::Matrix3f& K);

void loadNormalMap(image::Image<image::RGBColor> inputNormals, const image::Image<float>& normalsMask, image::Image<image::RGBfColor>& outputNormals);

void gradientMatrices_MAGMA(const image::Image<float>& mask, const std::vector<int>& maskIndexes, magma_d_matrix& Dup, magma_d_matrix& Dum, magma_d_matrix& Dvp, magma_d_matrix& Dvm, magma_queue_t queue);

}
}
