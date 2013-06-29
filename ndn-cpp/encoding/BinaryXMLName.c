/* 
 * Author: Jeff Thompson
 *
 * BSD license, See the LICENSE file for more information.
 */

#include "BinaryXMLDecoder.h"
#include "BinaryXML.h"
#include "BinaryXMLName.h"

char *ndn_decodeBinaryXMLName(struct ndn_Name *name, unsigned char *input, unsigned int inputLength)
{
  struct ndn_BinaryXMLDecoder decoder;
  ndn_BinaryXMLDecoder_init(&decoder, input, inputLength);
  
  char *error;
  if (error = ndn_BinaryXMLDecoder_readDTag(&decoder, ndn_BinaryXML_DTag_Name))
    return error;
    
  while (1) {
    int gotExpectedTag;
    if (error = ndn_BinaryXMLDecoder_peekDTag(&decoder, ndn_BinaryXML_DTag_Component, &gotExpectedTag))
      return error;
    
    if (!gotExpectedTag)
      // No more components.
      break;
    
    unsigned char *component;
    unsigned int componentLen;
    if (error = ndn_BinaryXMLDecoder_readBinaryDTagElement(&decoder, ndn_BinaryXML_DTag_Component, 0, &component, &componentLen))
      return error;
    
    // Add the component to the name.
    if (name->nComponents >= name->maxComponents)
      return "ndn_decodeBinaryXMLName: read a component past the maximum number of components allowed in the name";
    ndn_NameComponent_init(name->components + name->nComponents, component, componentLen);
    ++name->nComponents;
  }
  
  if (error = ndn_BinaryXMLDecoder_readElementClose(&decoder))
    return error;
  
  return 0;
}