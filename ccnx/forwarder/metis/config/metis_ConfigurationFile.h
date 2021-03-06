/*
 * Copyright (c) 2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Patent rights are not granted under this agreement. Patent rights are
 *       available under FRAND terms.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX or PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * @file metis_ConfigurationFile.h
 * @brief Accepts a filename and provides a means to read it into MetisConfiguration
 *
 * Reads a configuration file and converts the lines in to configuration commands for use
 * in MetisConfiguration.
 *
 * Accepts '#' lines as comments.  Skips blank and whitespace-only lines.
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef Metis__metis_ConfigurationFile_h
#define Metis__metis_ConfigurationFile_h

#include <ccnx/forwarder/metis/core/metis_Forwarder.h>

struct metis_configuration_file;
typedef struct metis_configuration_file MetisConfigurationFile;

/**
 * Creates a MetisConfigurationFile to prepare to process the file
 *
 * Prepares the object and opens the file.  Makes sure we can read the file.
 * Does not read the file or process any commands from the file.
 *
 * @param [in] metis An allocated MetisForwarder to configure with the file
 * @param [in] filename The file to use
 *
 * @retval non-null An allocated MetisConfigurationFile that is readable
 * @retval null An error
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
MetisConfigurationFile *metisConfigurationFile_Create(MetisForwarder *metis, const char *filename);

/**
 * Reads the configuration file line-by-line and issues commands to MetisConfiguration
 *
 * Reads the file line by line.  Skips '#' and blank lines.  Creates CPI objects from the
 * lines and feeds them to MetisConfiguration.
 *
 * Will stop on the first error.  Lines already processed will not be un-done.
 *
 * @param [in] configFile An allocated MetisConfigurationFile
 *
 * @retval true The entire files was processed without error.
 * @retval false There was an error in the file.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
bool metisConfigurationFile_Process(MetisConfigurationFile *configFile);

/**
 * Closes the underlying file and releases memory
 *
 * <#Paragraphs Of Explanation#>
 *
 * @param [in,out] configFilePtr An allocated MetisConfigurationFile that will be NULL'd as output
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
void metisConfigurationFile_Release(MetisConfigurationFile **configFilePtr);

#endif /* defined(Metis__metis_ConfigurationFile_h) */
