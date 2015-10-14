#include "CUDABlockMatchingKernel.h"
#include "_reg_blockMatching_cuda.h"

/* *************************************************************** */
CudaBlockMatchingKernel::CudaBlockMatchingKernel(Content *conIn, std::string name) :
   BlockMatchingKernel(name)
{
   //get CudaContent ptr
   con = static_cast<CudaContent*>(conIn);

   //get cpu ptrs
   reference = con->Content::getCurrentReference();
   params = con->Content::getBlockMatchingParams();

   //get cuda ptrs
   referenceImageArray_d = con->getReferenceImageArray_d();
   warpedImageArray_d = con->getWarpedImageArray_d();
   referencePosition_d = con->getReferencePosition_d();
   warpedPosition_d = con->getWarpedPosition_d();
   totalBlock_d = con->getTotalBlock_d();
   mask_d = con->getMask_d();
   referenceMat_d = con->getReferenceMat_d();
}
/* *************************************************************** */
void CudaBlockMatchingKernel::calculate()
{
   block_matching_method_gpu(reference,
                             params,
                             &referenceImageArray_d,
                             &warpedImageArray_d,
                             &referencePosition_d,
                             &warpedPosition_d,
                             &totalBlock_d,
                             &mask_d,
                             &referenceMat_d);
}
/* *************************************************************** */
