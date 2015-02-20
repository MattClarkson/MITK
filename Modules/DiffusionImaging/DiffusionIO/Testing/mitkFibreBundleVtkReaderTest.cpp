/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include <mitkTestingMacros.h>
#include <mitkFileReaderRegistry.h>
#include <mitkMimeType.h>
#include <usModuleInitialization.h>

/**
 * @brief Tests instantiating an IFileReader for .trk format.
 */
int mitkFibreBundleVtkReaderTest(int argc , char**)
{
  // always start with this!
  MITK_TEST_BEGIN("mitkFibreBundleVtkReaderTest")
  MITK_TEST_CONDITION_REQUIRED(argc == 1,"Testing invocation.")

  // The test, try to read a file of mime-type/file extension trk.
  mitk::FileReaderRegistry readerRegistry;
  std::vector<mitk::IFileReader*> readers = readerRegistry.GetReaders(mitk::FileReaderRegistry::GetMimeTypeForFile("trk"));
  MITK_TEST_CONDITION_REQUIRED(readers.size() >= 1, "Testing for >=1 registered readers, but found " << readers.size())

  // always end with this!
  MITK_TEST_END();
}
US_INITIALIZE_MODULE
