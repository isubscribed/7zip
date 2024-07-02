param (
    [Parameter(Mandatory)][string] $rootPath
)

$VersionFile = Get-Content $rootPath\C\7zVersion.h -Raw
$RegexProductVersion = 'MY_VERSION_NUMBERS[\s=]+"(?<version>[\d\.]+)"'

if ($VersionFile -match $RegexProductVersion) {
  $match = $Matches.version
}
else
{
    $match = "Unknown"
}

return $match
