#ifndef NLSR_LSA_SERVICEINFO_LSA_HPP
#define NLSR_LSA_SERVICEINFO_LSA_HPP

#include "lsa.hpp"

namespace nlsr {

class ServiceInfoLsa : public Lsa
{
public:
  ServiceInfoLsa() = default;
  ServiceInfoLsa(const ndn::Name& originRouter, uint64_t seqNo,
                 const ndn::time::system_clock::time_point& timepoint,
                 const std::string& serviceName, double processingTime,
                 int serviceCount, double loadIndex);

  explicit ServiceInfoLsa(const ndn::Block& block);

  Lsa::Type getType() const override { return type(); }
  static constexpr Lsa::Type type() { return Lsa::Type::SERVICE_INFO; }

  const std::string& getServiceName() const { return m_serviceName; }
  double getProcessingTime() const { return m_processingTime; }
  int getServiceCount() const { return m_serviceCount; }
  double getLoadIndex() const { return m_loadIndex; }

  template<ndn::encoding::Tag TAG>
  size_t wireEncode(ndn::EncodingImpl<TAG>& block) const;
  
  const ndn::Block& wireEncode() const override;
  void wireDecode(const ndn::Block& wire);

private:
  void print(std::ostream& os) const override;

private:
  std::string m_serviceName;
  double m_processingTime;
  int m_serviceCount;
  double m_loadIndex;
};

NDN_CXX_DECLARE_WIRE_ENCODE_INSTANTIATIONS(ServiceInfoLsa);

} // namespace nlsr

#endif // NLSR_LSA_SERVICEINFO_LSA_HPP