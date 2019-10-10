Pod::Spec.new do |s|
  s.name             = 'RangersAppLog'
  s.version          = '4.0.1'
  s.summary          = 'ByteDance Rangers AppLog.'
  s.description      = 'ByteDance Rangers AppLog SDK.'
  s.homepage         = 'https://github.com/bytedance/RangersAppLog'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'duanwenbin' => 'duanwenbin@bytedance.com' }
  s.source           = { :git => 'https://github.com/bytedance/RangersAppLog.git', :tag => s.version.to_s }

  s.ios.deployment_target = '8.0'
  s.requires_arc = true
  s.static_framework = true
  s.frameworks = 'Foundation','Security','AdSupport','CoreTelephony','CoreFoundation','SystemConfiguration','UIKit','WebKit'
  s.library = 'z','sqlite3'
  s.pod_target_xcconfig = { 'OTHER_LDFLAGS' => '-lObjC' }
  s.vendored_frameworks = 'RangersAppLog/*.framework'

end
