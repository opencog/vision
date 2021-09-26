#ifndef _OPENCOG_IMAGE_VALUE_H_
#define _OPENCOG_IMAGE_VALUE_H_

#include <opencog/atoms/atom_types/atom_types.h>
#include <opencog/atoms/value/FloatValue.h>
#include <opencog/atoms/value/Value.h>
#include <opencog/atoms/value/ValueFactory.h>
#include <opencog/atomspace/AtomSpace.h>
#include <typeindex>

namespace opencog {
    /** \addtogroup grp_vision
     *  @{
     */

    // ImageValue holds image data (OpenCV data type).
    // It is used for storing results of operating on images.

    class ImageValue : public FloatValue {
    private:
        Handle _item;

    protected:
        void update() const;

    public:
        /**
         * @param hseq a HandleSeq of size two. The first atom denotes the item
         * to store and the second one is the the ImageNode instance to store
         * the atom into.
         */
        ImageValue(const HandleSeq& hseq);
        virtual ~ImageValue() {}

        bool operator==(const Value& other) const;

        std::string to_string(const std::string& indent = "") const;
    };

    typedef std::shared_ptr<const ImageValue> ImageValuePtr;
    static inline ImageValuePtr ImageValueCast(const ValuePtr& a) {
        return std::dynamic_pointer_cast<const ImageValue>(a);
    }

    template <typename... Type>
    static inline std::shared_ptr<ImageValue> createImageValue(Type&&... args) {
        return std::make_shared<ImageValue>(std::forward<Type>(args)...);
    }

    /** @}*/
} // namespace opencog
#endif
