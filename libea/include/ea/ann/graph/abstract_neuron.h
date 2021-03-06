/* neuron.h
 *
 * This file is part of EALib.
 *
 * Copyright 2012 David B. Knoester.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _ANN_ABSTRACT_NEURON_H_
#define _ANN_ABSTRACT_NEURON_H_

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/base_object.hpp>

namespace ann {
    //! Flag bits for neurons.
    namespace neuron {
        enum flags { reserved=0x01, top=0x02, bias=0x04, input=0x08, output=0x010, hidden=0x020 };
    }
    
    typedef unsigned int flag_type;
    
    /*! Convenience struct to hold flags for a vertex.
     */
    struct neuron_flags {
        neuron_flags() : _flags(0) { }
        bool getf(flag_type f) { return _flags & f; }
        void setf(flag_type f) { _flags |= f; }
        flag_type flags() { return _flags; }
        flag_type flags(flag_type f) { _flags = f; return _flags; }

        flag_type _flags; //!< Flags.
    };
    
	/*! Abstract base class for neurons.
	 */
	struct abstract_neuron : public neuron_flags {
        
        //! Synapse type for feed forward neurons.
        struct abstract_synapse {
            //! Default constructor.
            abstract_synapse(double w=0.05) : weight(w) { }

            //! Serializer for abstract synapse types.
            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar & BOOST_SERIALIZATION_NVP(weight);
            }
            
            double weight; //!< Weight of this edge.
        };

		//! Constructor.
		abstract_neuron() : input(0.0), output(0.0) { }
        
        //! Serializer for abstract neuron types.
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version) {
            ar & boost::serialization::make_nvp("flags", _flags);
            ar & BOOST_SERIALIZATION_NVP(input);
            ar & BOOST_SERIALIZATION_NVP(output);
        }

        double input; //!< Input to this neuron.
		double output; //!< Output from this neuron.
	};
    
} // nn

#endif
