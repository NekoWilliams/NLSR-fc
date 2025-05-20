#include "serviceinfo-lsa.hpp"
#include "tlv-nlsr.hpp"

namespace nlsr {

ServiceInfoLsa::ServiceInfoLsa(const ndn::Name& originRouter, uint64_t seqNo,
                               const ndn::time::system_clock::time_point& timepoint,
                               const std::string& serviceName, double processingTime,
                               int serviceCount, double loadIndex)
  : Lsa(originRouter, seqNo, timepoint),
    m_serviceName(serviceName),
    m_processingTime(processingTime),
    m_serviceCount(serviceCount),
    m_loadIndex(loadIndex)
{}

ServiceInfoLsa::ServiceInfoLsa(const ndn::Block& block)
{
  wireDecode(block);
}

template<ndn::encoding::Tag TAG>
size_t ServiceInfoLsa::wireEncode(ndn::EncodingImpl<TAG>& block) const {
  size_t totalLength = Lsa::wireEncode(block);
  totalLength += prependStringBlock(block, nlsr::tlv::ServiceName, m_serviceName);
  totalLength += prependDoubleBlock(block, nlsr::tlv::ProcessingTime, m_processingTime);
  totalLength += prependNonNegativeIntegerBlock(block, nlsr::tlv::ServiceCount, m_serviceCount);
  totalLength += prependDoubleBlock(block, nlsr::tlv::LoadIndex, m_loadIndex);
  return totalLength;
}

void ServiceInfoLsa::wireDecode(const ndn::Block& wire) {
  Lsa::wireDecode(wire);
  auto elements = wire.elements_begin();
  for (; elements != wire.elements_end(); ++elements) {
    if (elements->type() == nlsr::tlv::ServiceName) {
      m_serviceName = readString(*elements);
    } else if (elements->type() == nlsr::tlv::ProcessingTime) {
      m_processingTime = readDouble(*elements);
    } else if (elements->type() == nlsr::tlv::ServiceCount) {
      m_serviceCount = readNonNegativeInteger(*elements);
    } else if (elements->type() == nlsr::tlv::LoadIndex) {
      m_loadIndex = readDouble(*elements);
    }
  }
}

void ServiceInfoLsa::print(std::ostream& os) const {
  Lsa::print(os);
  os << "      Service Name      : " << m_serviceName << "\n"
     << "      Processing Time   : " << m_processingTime << " ms\n"
     << "      Service Count     : " << m_serviceCount << "\n"
     << "      Load Index        : " << m_loadIndex << "\n";
}

} // namespace nlsr