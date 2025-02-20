//----------------------------------------------------------------------------
//
// TSDuck - The MPEG Transport Stream Toolkit
// Copyright (c) 2005-2022, Thierry Lelegard
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
// THE POSSIBILITY OF SUCH DAMAGE.
//
//----------------------------------------------------------------------------
//!
//!  @file
//!  Representation of an ISDB event_group_descriptor.
//!
//----------------------------------------------------------------------------

#pragma once
#include "tsAbstractDescriptor.h"

namespace ts {

    //!
    //! Representation of an ISDB event_group_descriptor.
    //! @see ARIB STD-B10, Part 2, 6.2.34
    //! @ingroup descriptor
    //!
    class TSDUCKDLL EventGroupDescriptor : public AbstractDescriptor
    {
    public:
        //!
        //! Actual event entry.
        //!
        struct TSDUCKDLL ActualEvent
        {
            ActualEvent();        //!< Constructor.
            uint16_t service_id;  //!< Service id.
            uint16_t event_id;    //!< Event id.
        };

        //!
        //! Actual network event entry.
        //!
        struct TSDUCKDLL OtherEvent
        {
            OtherEvent();                  //!< Constructor.
            uint16_t original_network_id;  //!< Original network id.
            uint16_t transport_stream_id;  //!< Transport stream id.
            uint16_t service_id;           //!< Service id.
            uint16_t event_id;             //!< Event id.
        };

        typedef std::list<ActualEvent> ActualEventList;  //!< List of actual events.
        typedef std::list<OtherEvent> OtherEventList;    //!< List of other events.

        // EventGroupDescriptor public members:
        uint8_t         group_type;     //!< 4 bits, group type.
        ActualEventList actual_events;  //!< List of actual events.
        OtherEventList  other_events;   //!< List of other events, when group_type == 4 or 5.
        ByteBlock       private_data;   //!< Private data for other group types.

        //!
        //! Default constructor.
        //!
        EventGroupDescriptor();

        //!
        //! Constructor from a binary descriptor
        //! @param [in,out] duck TSDuck execution context.
        //! @param [in] bin A binary descriptor to deserialize.
        //!
        EventGroupDescriptor(DuckContext& duck, const Descriptor& bin);

        // Inherited methods
        DeclareDisplayDescriptor();

    protected:
        // Inherited methods
        virtual void clearContent() override;
        virtual void serializePayload(PSIBuffer&) const override;
        virtual void deserializePayload(PSIBuffer&) override;
        virtual void buildXML(DuckContext&, xml::Element*) const override;
        virtual bool analyzeXML(DuckContext&, const xml::Element*) override;
    };
}
