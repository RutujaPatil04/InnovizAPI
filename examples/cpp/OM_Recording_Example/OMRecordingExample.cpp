// Copyright 2021 Innoviz Technologies
//
// Licensed under the Innoviz Open Dataset License Agreement (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://github.com/InnovizTechnologies/InnovizAPI/blob/main/LICENSE.md
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

///////////////////////////////////////////////////////////
//  OMRecordingExample.cpp
//  Implementation of the Class OMRecordingExample
//  Created on:      07-Oct-2020 1:13:23 AM
//  Original author: julia.sher
///////////////////////////////////////////////////////////

#include "OMRecordingExample.h"
#include "../common/CommonUtils.h"
#include "data_point/Datapoint.h"
#include <iostream>


OMRecordingExample::OMRecordingExample(std::string recording_path)
{
	m_reader.reset(invz::FileReaderInit(recording_path));
}



OMRecordingExample::~OMRecordingExample(){

	if (m_reader)
		FileReaderClose(m_reader.release());
}



void OMRecordingExample::initUserBuffers(size_t buffersCount, std::vector<invz::FrameDataUserBuffer>& userBuffers, std::vector<invz::FrameDataAttributes>& attributes)
{
	// Initialize User Buffers
	for (size_t i = 0; i < buffersCount; i++)
	{
		if (attributes[i].known_type == invz::GRAB_TYPE_MEASURMENTS_REFLECTION0)
		{
			invz::FrameDataUserBuffer&& userBuffer(attributes[i]);
			userBuffers.push_back(userBuffer);
		}
	}
}


void OMRecordingExample::GetNumberOfFrames()
{
	// Read number of frames from file
	size_t frames;
	m_reader->GetNumOfFrames(frames);
	std::cout << std::endl;
	std::cout << "Number of frames: " << frames << std::endl;
}


void OMRecordingExample::GetFileMetaData()
{
	//Read file meta data
	invz::DeviceMeta file_meta;
	m_reader->GetDeviceMetadata(file_meta);
	std::cout << std::endl;
	std::cout << "File meta data: " << std::endl;
	std::cout << "\t" << "number of lrfs: " << file_meta.lrf_count << std::endl;
	for (uint32_t i = 0; i < file_meta.lrf_count; ++i)
	{
		int lrf_height = file_meta.lrf_height[i];
		int lrf_width = file_meta.lrf_width[i];

		std::cout << "\t" << "lrf " << i << " height: " << lrf_height << std::endl;
		std::cout << "\t" << "lrf " << i << " width: " << lrf_width << std::endl;
	}
}


void OMRecordingExample::ReadFrames()
{
	std::vector<invz::FrameDataAttributes> attributes;
	attributes.resize(DemoConfig::max_num_of_buffers);

	// buffersCount holds the actual number of existing buffers - returned by GetFrameDataAttributes
	size_t buffersCount = DemoConfig::max_num_of_buffers;
	m_reader->GetFrameDataAttributes(attributes.data(), buffersCount);

	// buffers to read the required data - 
	// GRAB_TYPE_MEASURMENTS_REFLECTION0
	initUserBuffers(buffersCount, m_userBuffers, attributes);

	// Initialize to default values - returned by GrabFrame
	uint32_t frameNumber = UINT32_MAX;
	uint64_t timeStamp = 0;

	// Read Frame required data into userBuffers initialized above 
	size_t frames;
	m_reader->GetNumOfFrames(frames);

	std::cout << std::endl;
	std::cout << "Reading " << frames << " frames ... " << std::endl;
	for (uint32_t frame_index = 0; frame_index < frames; ++frame_index)
	{
		auto result = m_reader->GrabFrame(m_userBuffers.data(), (uint32_t)m_userBuffers.size(), frameNumber, timeStamp, frame_index);

		if (result.error_code == invz::ERROR_CODE_OK)
		{
			if (m_userBuffers[static_cast<size_t>(EOMDataType::Ref0)].status == invz::USER_BUFFER_FULL)
			{
				std::cout << std::endl;
				std::cout << "\tFrame number: " << frameNumber << std::endl; 
				CommonUtils::HandleReflection0Data(m_userBuffers[static_cast<size_t>(EOMDataType::Ref0)]);
			}
		}
	}
	std::cout << std::endl;
	std::cout << "Finished reading frames." << std::endl;
}


int main(void)
{
	std::string recordings_path = "../../example_recordings";
	std::string recording = "Lidar_1.invz4_4";
	std::unique_ptr<OMRecordingExample> m_OMRecordingExample = std::make_unique<OMRecordingExample>(recordings_path + "/" + recording);

	bool stop = false;
	while (!stop)
	{
		std::cout << "\n Please select the required demo: " << std::endl;
		std::cout << "\t1 - Read frames from OM recording" << std::endl;
		std::cout << "\t2 - Get OM recording number of frames" << std::endl;
		std::cout << "\t3 - Get OM recording metadata" << std::endl;
		std::cout << "\tq - Quit" << std::endl;

		char user;
		std::cin >> user;
		switch (user)
		{
		case '1':
			m_OMRecordingExample->ReadFrames();
			break;
		case '2':
			m_OMRecordingExample->GetNumberOfFrames();
			break;
		case '3':
			m_OMRecordingExample->GetFileMetaData();
			break;
		case 'q':
			stop = true;
			break;
		default:
			std::cout << "Unsupported! Try again" << std::endl;
			break;
		}
	}
	return 0;
}